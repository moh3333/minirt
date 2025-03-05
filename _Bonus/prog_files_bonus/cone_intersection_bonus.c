/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:51:12 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/03 17:41:15 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

void	*first_algo(double arr[4], t_intersect *ret)
{
	if (fabs(arr[1]) == 0.0 && fabs(arr[0]) == 0.0)
		return (NULL);
	ret->t[0] = -arr[2] / arr[1];
	ret->t[1] = -INFINITY;
	return ("ok");
}

void	*intersect_between_co_bounds(double arr[4], t_ray *r_ob_space, \
								t_cone *co, t_intersect *ret)
{
	double	in_bounds[2];

	arr[3] = sq(arr[1]) - (4.0 * arr[0] * arr[2]);
	if (arr[3] < 0.0)
		return (NULL);
	ret->t[0] = (-arr[1] - sqrt(arr[3])) / (2.0 * arr[0]);
	ret->t[1] = (-arr[1] + sqrt(arr[3])) / (2.0 * arr[0]);
	if (ret->t[0] > ret->t[1] && ret->t[1] != -INFINITY)
		swap(&ret->t[0], &ret->t[1]);
	in_bounds[0] = r_ob_space->o.y + ret->t[0] * r_ob_space->d.y;
	if (!(co->min <= in_bounds[0] && in_bounds[0] <= co->max))
		ret->t[0] = -INFINITY;
	in_bounds[1] = r_ob_space->o.y + ret->t[1] * r_ob_space->d.y;
	if (!(co->min <= in_bounds[1] && in_bounds[1] <= co->max))
		ret->t[1] = -INFINITY;
	if (ret->t[0] == -INFINITY && ret->t[1] == -INFINITY)
		return (NULL);
	return ("OK");
}

t_intersect	*cone_intersect(t_ray *r, t_cone *co)
{
	t_ray		*r_ob_space;
	t_intersect	*ret;
	double		arr[4];

	ret = new_intersect();
	r_ob_space = transform(r, co->inverse_m);
	arr[0] = sq(r_ob_space->d.x) - sq(r_ob_space->d.y) + sq(r_ob_space->d.z);
	arr[1] = 2.0 * ((r_ob_space->o.x * r_ob_space->d.x) + \
	(r_ob_space->o.z * r_ob_space->d.z) - (r_ob_space->o.y * r_ob_space->d.y));
	arr[2] = sq(r_ob_space->o.x) + sq(r_ob_space->o.z) - sq(r_ob_space->o.y);
	if (arr[0] <= 0.0 && !(arr[1] <= 0.0))
		first_algo(arr, ret);
	if (!intersect_between_co_bounds(arr, r_ob_space, co, ret))
		return (NULL);
	// intersect_caps_co(co, r_ob_space, &ret->t[0], &ret->t[1]);
	ret->object.shape_co = *co;
	ret->object.type = CONE;
	ret->ray = r_ob_space;
	ret->next = NULL;
	return (ret);
}

void	intersect_caps_co(t_cone *co, t_ray *r, double *t1, double *t2)
{
	double	t;

	if (fabs(r->d.y) < EPSILON)
		return ;
	t = (co->min - r->o.y) / r->d.y;
	if (check_cap(r, t) && (*t1 == -INFINITY))
			*t1 = t;
	t = (co->max - r->o.y) / r->d.y;
	if (check_cap(r, t) && (*t2 == -INFINITY))
			*t2 = t;
}
