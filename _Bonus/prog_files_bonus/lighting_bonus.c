/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:35:03 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 21:59:50 by mthamir          ###   ########.fr       */
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
	if (reflect_dot_eye < 0.0)
		return (NULL);
	factor = pow(reflect_dot_eye, 200.0);
	return (color_s_mul(&light->color, (0.7 * factor)));
}

t_color	*check_pattern(t_comps *comp, t_material *m, int type)
{
	t_tuple	*p;

	if (type == PLANE)
	{
		p = tup_mat_mul (comp->object.shape_pl.inverse_m, comp->point);
		if ((int )fabs(floor(p->x / m->checker) \
			+ floor(p->z / m->checker)) % 2 != 0)
			return (&m->pattern_color);
	}
	else if (type == SPHER && spher_checker(&comp->object.shape, comp))
		return (&m->pattern_color);
	return (&m->color);
}
