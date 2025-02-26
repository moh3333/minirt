/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:19:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:19:48 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_intersect	*get_first_intersect(t_intersect *list, t_ray *r)
{
	t_intersect	*tmp;
	t_intersect	*ret;

	ret = new_intersect();
	tmp = list;
	ret->ray = r;
	ret->t[0] = HUGE_VAL;
	while (tmp)
	{
		if (hit(tmp->t))
		{
			tmp->t[0] = get_closest(tmp->t);
			if (tmp->t[0] < ret->t[0])
			{
				ret->t[0] = tmp->t[0];
				ret->object = tmp->object;
			}
		}
		tmp = tmp->next;
	}
	if (ret->t[0] == HUGE_VAL)
		return (NULL);
	return (ret);
}

double	get_closest(double *t)
{
	if (t[0] < EPSILON && t[1] >= EPSILON)
		return (t[1]);
	else if (t[1] < EPSILON && t[0] >= EPSILON)
		return (t[0]);
	return (fmin(t[0], t[1]));
}

double	hit(double *arr)
{
	return (!(arr[0] < EPSILON && arr[1] < EPSILON));
}