/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:35:03 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/16 14:47:34 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

t_light	*light_source(t_tuple *position, t_color *color, double brightness)
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
	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	mate->checker = 0;
	return (mate);
}

t_color *compute_specular(t_material *m, \
				t_light *light, t_tuple *lightv, t_tuple *normalv, t_tuple *eyev)
{
	double reflect_dot_eye;
	double factor;
	double var;

	opp(lightv);
	reflect_dot_eye =  dot_p(*reflect(*lightv, *normalv), *eyev);
	if (reflect_dot_eye <= 0.0)
		return (NULL);
	factor = pow(reflect_dot_eye, m->shininess);
	var = m->specular * factor;
	return (color_s_mul(&light->color, var));
}

t_color *check_pattern(t_tuple *p, t_material *m)
{
	if ((int )fabs(floor(p->x/m->checker) + floor(p->z/m->checker)) % 2 == 0)
		return (&m->color);
	return (&m->pattern_color);
}

t_color	*shade_hit(t_world *w, t_comps *comp, t_tuple *eyev)
{
	t_material	*m;
	t_color *ambiant;
	t_color *col;
	int i = 0;
	t_color *specular_diffuse = new_color(0,0,0);

	if (!comp)
		return (new_color(0, 0, 0));
	if (comp->object.type == SPHER)
		m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		m = comp->object.shape_cyl.material;
	col = &m->color;
	if (comp->object.type == PLANE && m->checker)
		col = check_pattern(tup_mat_mul(comp->object.shape_pl.inverse_m, comp->point), m);
	ambiant = colors_operation(w->ambiant_color, col, mul);
	while (i < w->light_count){
		if (!in_shadow(w, comp, i))
		{
			specular_diffuse =  colors_operation(specular_diffuse, \
				compute_lightning(m, &w->light[i], comp->point, comp->normalv, eyev, col), add);
		}
		i++;
	}	
	return (colors_operation(ambiant, specular_diffuse, add));
}

t_color	*compute_lightning(t_material *m, \
				t_light *light, t_tuple *pos, t_tuple *normalv, t_tuple *eyev, t_color *col)
{
	t_color	*effective_color;
	t_color	*diffuse;
	t_tuple	*lightv;
	double	light_dot_normal;
	t_color *specular;

	diffuse = NULL;
	specular = NULL;
	effective_color = colors_operation(&light->color, col, mul);
	lightv = tpl_o(light->position, *pos, sub);
	normalize(lightv);
	light_dot_normal = dot_p(*lightv,*normalv);
	if (light_dot_normal >= 0.0)
		diffuse = color_s_mul(effective_color, light_dot_normal);
	if (diffuse)
		specular = compute_specular(m, light, lightv, normalv, eyev);
	return (colors_operation(diffuse, specular, add));
}

t_intersect	*new_intersect(void)
{
	t_intersect	*ret;

	ret = ft_malloc(sizeof(t_intersect), 0);
	ret->next = NULL;
	return (ret);
}
