/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:20:45 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 20:43:31 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

void	*intersect_between_bounds(double arr[4], t_ray *r_ob_space, \
								t_cylinder *cyl, t_intersect *ret)
{
	double	in_bounds[2];

	arr[1] = 2.0 * ((r_ob_space->o.x * r_ob_space->d.x) \
			+ (r_ob_space->o.z * r_ob_space->d.z));
	arr[2] = sq(r_ob_space->o.x) + sq(r_ob_space->o.z) - 1;
	arr[3] = sq(arr[1]) - (4.0 * arr[0] * arr[2]);
	if (arr[3] < 0.0)
		return (NULL);
	ret->t[0] = (-arr[1] - sqrt(arr[3])) / (2.0 * arr[0]);
	ret->t[1] = (-arr[1] + sqrt(arr[3])) / (2.0 * arr[0]);
	if (ret->t[0] > ret->t[1])
		swap(&ret->t[0], &ret->t[1]);
	in_bounds[0] = r_ob_space->o.y + ret->t[0] * r_ob_space->d.y;
	if (!(cyl->min <= in_bounds[0] && in_bounds[0] <= cyl->max))
		ret->t[0] = -INFINITY;
	in_bounds[1] = r_ob_space->o.y + ret->t[1] * r_ob_space->d.y;
	if (!(cyl->min <= in_bounds[1] && in_bounds[1] <= cyl->max))
		ret->t[1] = -INFINITY;
	return ("OK");
}

t_intersect	*cyl_intersect(t_ray *r, t_cylinder *cyl)
{
	t_ray		*r_ob_space;
	t_intersect	*ret;
	double		arr[4];

	ret = new_intersect();
	r_ob_space = transform(r, cyl->inverse_m);
	arr[0] = sq(r_ob_space->d.x) + sq(r_ob_space->d.z);
	if (arr[0] > 0.0)
		if (!intersect_between_bounds(arr, r_ob_space, cyl, ret))
			return (NULL);
	ret->object.shape_cyl = *cyl;
	ret->object.type = CYLINDER;
	ret->ray = r_ob_space;
	ret->next = NULL;
	return (ret);
}
