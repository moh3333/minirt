/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _computing_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:38:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/04 23:06:18 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

t_comps	*new_comps(void)
{
	return (ft_malloc(sizeof(t_comps), 0));
}

bool	in_shadow(t_world *w, t_comps *comp, int i)
{
	t_tuple		*shadow_ray;
	t_intersect	*inter;
	t_ray		*r1;
	double		distance;

	shadow_ray = tpl_o(w->light[i].position, *comp->point, sub);
	distance = magnitude(*shadow_ray);
	comp->shadow = false;
	normalize(shadow_ray);
	r1 = ray(*comp->point, *shadow_ray);
	inter = world_intersection(w, r1);
	if (inter && (distance - inter->t[0]) >= EPSILON)
		comp->shadow = true;
	return (comp->shadow);
}

t_comps	*prepare_computing(t_intersect *list, t_ray *r)
{
	t_comps	*comp;

	if (!list)
		return (NULL);
	comp = new_comps();
	comp->t = list->t[0];
	comp->object = list->object;
	comp->point = position(r, comp->t);
	comp->eyev = cpv(r->d.x, r->d.y, r->d.z, 0);
	opp(comp->eyev);
	if (comp->object.type == SPHER)
	comp->normalv = normal_at(&comp->object.shape, comp->point);
	else if (comp->object.type == PLANE)
		comp->normalv = tup_mat_mul(comp->object.shape_pl.transform, \
		comp->object.shape_pl.normalv);
	else if (comp->object.type == CYLINDER)
		comp->normalv = normal_at_cyl(&comp->object.shape_cyl, comp->point);
	else if (comp->object.type == CONE)
		comp->normalv = normal_at_co(&comp->object.shape_co, comp->point);
	if (dot_p(*comp->normalv, *comp->eyev) < 0.0)
		opp(comp->normalv);
	return (comp);
}
