/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:09:20 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/02 19:43:01 by mthamir          ###   ########.fr       */
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
