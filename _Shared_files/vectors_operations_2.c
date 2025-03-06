/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:09:20 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/06 18:10:09 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_tuple	*position(t_ray *ray, double distance)
{
	return (tpl_o(ray->o, *(scalar(ray->d, distance)), add));
}

t_tuple	*reflect(t_tuple in, t_tuple normal)
{
	return (tpl_o(in, *(scalar(normal, mul(dot_p(in, normal), 2))), sub));
}

void	check_normal_range(t_tuple *normal)
{
	if (!(normal->x >= 0.0 && normal->x <= 1.0) && \
	(normal->y >= 0.0 && normal->y <= 1.0) && \
	(normal->z >= 0.0 && normal->z <= 1.0))
		return (print_error(INVALID_NORMAL));
	printf("%f  %f  %f\n", normal->x, normal->y, normal->z);
}
