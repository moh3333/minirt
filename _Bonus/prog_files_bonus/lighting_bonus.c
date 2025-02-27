/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:35:03 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/27 18:16:00 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

t_light	*light_source(t_tuple *position, t_color *color)
{
	t_light	*light;

	light = ft_malloc(sizeof(t_light), 0);
	light->position = *position;
	light->color = *color;
	return (light);
}

t_material	*material(void)
{
	t_material	*mate;

	mate = ft_malloc(sizeof(t_material), 0);
	mate->color = *new_color(1.0, 1.0, 1.0);
	mate->checker = 0;
	return (mate);
}

t_color	*compute_specular(t_light *light, \
	t_tuple *lightv, t_tuple *normalv, t_tuple *eyev)
{
	double	reflect_dot_eye;
	double	factor;

	opp(lightv);
	normalize(lightv);
	reflect_dot_eye = dot_p(*reflect(*lightv, *normalv), *eyev);
	if (reflect_dot_eye <= 0.0)
		return (NULL);
	factor = pow(reflect_dot_eye, 50.0);
	return (color_s_mul(&light->color, (0.7 * factor)));
}

t_color	*check_pattern(t_tuple *p, t_material *m)
{
	if ((int )fabs(floor(p->x / m->checker) \
		+ floor(p->z / m->checker)) % 2 == 0)
		return (&m->color);
	return (&m->pattern_color);
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
	if (comp->object.type == SPHER)
		m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		m = comp->object.shape_cyl.material;
	else if (comp->object.type == CONE)
		m = comp->object.shape_co.material;
	col = &m->color;
	// if (comp->object.type == SPHER && m->texter)
	// 	col = spher_texter(m,comp);
	if (comp->object.type == PLANE && m->checker)
		col = check_pattern(tup_mat_mul \
			(comp->object.shape_pl.inverse_m, comp->point), m);
	ambiant = colors_operation(w->ambiant_color, col, mul);
	while (i < w->light_count)
	{
		if (!in_shadow(w, comp, i))
			specular_diffuse = colors_operation(specular_diffuse, \
				compute_lightning(&w->light[i], \
					comp->point, comp->normalv, eyev, col), add);
		i++;
	}
	return (colors_operation(ambiant, specular_diffuse, add));
}

t_color	*compute_lightning(t_light *light, \
	t_tuple *pos, t_tuple *normalv, t_tuple *eyev, t_color *col)
{
	t_color	*effective_color;
	t_color	*diffuse;
	t_tuple	*lightv;
	double	light_dot_normal;
	t_color	*specular;

	diffuse = NULL;
	specular = NULL;
	effective_color = colors_operation(&light->color, col, mul);
	lightv = tpl_o(light->position, *pos, sub);
	normalize(lightv);
	light_dot_normal = dot_p(*lightv,*normalv);
	if (light_dot_normal >= 0.0)
		diffuse = color_s_mul(effective_color, light_dot_normal * 0.9);
	if (diffuse)
		specular = compute_specular(light, lightv, normalv, eyev);
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
