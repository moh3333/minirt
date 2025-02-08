/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:35:03 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/08 13:13:07 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_light	*light_source(t_tuple *position, t_color *color, double brightness)
{
	t_light	*light;

	light = ft_malloc(sizeof(t_light), 0);
	light->position = *position;
	light->brightness = brightness;
	light->color = *color;
	return (light);
}

t_material	*material(void)
{
	t_material	*mate;

	mate = ft_malloc(sizeof(t_material), 0);
	mate->color = *new_color(1.0, 1.0, 1.0);
	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	return (mate);
}

t_color	*shade_hit(t_world *w, t_comps *comp)
{
	t_material	*m;

	if (!comp)
		return (new_color(0, 0, 0));
	if (comp->object.type == SPHER)
		m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		m = comp->object.shape_cyl.material;
	if (comp->shadow)
		return (color_s_mul(colors_operation(color_s_mul(&w->light->color, \
				w->light->brightness), &m->color, mul), m->ambiant));
	return (compute_lightning(m, w->light, comp->point, comp->normalv));
}

t_color	*compute_lightning(t_material *m, \
				t_light *light, t_tuple *pos, t_tuple *normalv)
{
	t_color	*effective_color;
	t_color	*ambiant;
	t_color	*diffuse;
	t_tuple	*lightv;
	double	light_dot_normal;

	diffuse = new_color(0.0, 0.0, 0.0);
	effective_color = colors_operation(color_s_mul(&light->color, \
					light->brightness), &m->color, mul);
	lightv = tpl_o(light->position, *pos, sub);
	normalize(lightv);
	ambiant = color_s_mul(effective_color, m->ambiant);
	light_dot_normal = dot_p(*lightv,*normalv);
	if (light_dot_normal >= EPSILON)
		diffuse = color_s_mul(colors_operation(&light->color, \
				&m->color, mul), (m->diffuse * light_dot_normal));
	return (colors_operation(diffuse, ambiant, add));
}

t_intersect	*new_intersect(void)
{
	t_intersect	*ret;

	ret = ft_malloc(sizeof(t_intersect), 0);
	ret->next = NULL;
	return (ret);
}
