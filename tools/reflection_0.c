/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:35:04 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/15 16:25:41 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
	return (tpl_o(in, (scalar(normal, mul(Dot_p(in, normal), 2))), '-'));
}

double get_closest(double *t)
{
	if (t[0] < 0 && t[1] > 0)
		return (t[1]);
	else if (t[1] < 0 && t[0] > 0)
		return (t[0]);
	else if (t[0] > 0 && t[1] > 0)
	{
		if (t[0] < t[1])
			return (t[0]);
		else if (t[0] > t[1])
			return (t[1]);
		else if (t[0] == t[1])
			return (t[1]);
	}
	return (0);
}

t_material *material()
{
	t_material *mate = ft_malloc(sizeof(t_material));

	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	return (mate);
}

t_color *compute_lightning(t_material *m, t_light *light, t_tuple *pos,t_tuple *normalv)
{
	t_tuple *lightv = Normalize(tpl_o(light->position, pos, '-'));
	t_color *ambiant = to_rgba(m->ambiant * light->brightness);
	double light_dot_normal = Dot_p(lightv, normalv);
	t_color *diffuse;
	if(light_dot_normal < EPSILON)
		diffuse = new_color(0.0,0.0,0.0);
	else
		diffuse = color_s_mul(m->color, (m->diffuse * light_dot_normal * light->brightness));
	return (colors_operation(diffuse, ambiant, '+'));
}