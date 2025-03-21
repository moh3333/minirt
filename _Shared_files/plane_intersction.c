/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:10:27 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 20:40:16 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_intersect	*pl_intersect(t_ray *r1, t_plane *pl)
{
	t_intersect	*ret;
	t_ray		*r_ob_space;

	r_ob_space = transform(r1, pl->inverse_m);
	ret = new_intersect();
	if (fabs(r_ob_space->d.y) < EPSILON)
		return (NULL);
	ret->t[0] = -(r_ob_space->o.y) / r_ob_space->d.y;
	if (ret->t[0] < EPSILON)
		return (NULL);
	ret->object.shape_pl = *pl;
	ret->object.type = PLANE;
	ret->ray = r_ob_space;
	ret->next = NULL;
	return (ret);
}
