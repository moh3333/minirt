/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:08:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/07 23:21:46 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

static double	*eq_inter(t_ray *ray1, double arr[])
{
	arr[0] = dot_p(ray1->d, ray1->d);
	arr[1] = 2.0 * (dot_p(ray1->o, ray1->d));
	arr[2] = (dot_p(ray1->o, ray1->o) - 1);
	arr[3] = sq(arr[1]) - (4.0 * (arr[0] * arr[2]));
	return (arr);
}

t_intersect	*intersect(t_ray *ray, t_spher *sph)
{
	t_intersect	*inter;
	t_ray		*ray1;
	double		arr[6];

	ray1 = transform(ray, sph->inverse_m);
	eq_inter(ray1, arr);
	inter = new_intersect();
	if (!inter || arr[3] < 0.0)
		return (NULL);
	arr[4] = (2 * (arr[0]));
	arr[5] = sqrt(arr[3]);
	inter->t[0] = (-arr[1] - arr[5]) / arr[4];
	inter->t[1] = (-arr[1] + arr[5]) / arr[4];
	inter->object.type = SPHER;
	inter->object.shape = *sph;
	inter->ray = ray1;
	inter->next = NULL;
	return (inter);
}
