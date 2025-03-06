/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_phony_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:49:50 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 18:24:46 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

static void	check_object_type(t_comps *comp, t_material **m, t_color **col)
{
	if (comp->object.type == SPHER)
		*m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		*m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		*m = comp->object.shape_cyl.material;
	else if (comp->object.type == CONE)
		*m = comp->object.shape_co.material;
	*col = &(*m)->color;
	if (comp->object.type == SPHER && (*m)->texter)
		*col = spher_texter(&comp->object.shape, *m, comp);
	if (comp->object.type == PLANE && (*m)->checker)
		*col = check_pattern(tup_mat_mul \
			(comp->object.shape_pl.inverse_m, comp->point), *m);
}

t_color	*shade_hit(t_world *w, t_comps *comp, t_tuple *eyev)
{
	t_material	*m;
	t_color		*ambiant;
	t_color		*col;
	t_color		*specular_diffuse;
	int			i;

	i = 0;
	specular_diffuse = new_color(0, 0, 0);
	m = NULL;
	if (!comp)
		return (new_color(0, 0, 0));
	col = NULL;
	check_object_type(comp, &m, &col);
	ambiant = colors_operation(w->ambiant_color, col, mul);
	while (i < w->light_count)
	{
		if (!in_shadow(w, comp, i) || \
			(comp->object.type == SPHER && (m->texter || m->bump_map)))
			specular_diffuse = colors_operation(specular_diffuse, \
			compute_lightning_b(&w->light[i], comp, eyev, col), add);
		i++;
	}
	return (colors_operation(ambiant, specular_diffuse, add));
}

t_color	*compute_lightning_b(t_light *light, \
	t_comps *comp, t_tuple *eyev, t_color *col)
{
	t_color	*effective_color;
	t_color	*diffuse;
	t_tuple	*lightv;
	double	light_dot_normal;
	t_color	*specular;

	diffuse = NULL;
	specular = NULL;
	effective_color = colors_operation(&light->color, col, mul);
	lightv = tpl_o(light->position, *comp->point, sub);
	normalize(lightv);
	light_dot_normal = dot_p(*lightv,*comp->normalv);
	if (light_dot_normal >= 0.0)
		diffuse = color_s_mul(effective_color, light_dot_normal);
	if (diffuse)
		specular = compute_specular(light, lightv, comp->normalv, eyev);
	return (colors_operation(diffuse, specular, add));
}

t_intersect	*new_intersect(void)
{
	t_intersect	*ret;

	ret = ft_malloc(sizeof(t_intersect), 0);
	ret->t[0] = 0.0;
	ret->t[1] = 0.0;
	ret->next = NULL;
	return (ret);
}
