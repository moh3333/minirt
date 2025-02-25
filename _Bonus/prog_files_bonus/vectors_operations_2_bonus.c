/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:53:42 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/25 18:34:25 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"
/*get the position of a point in a ray */
t_tuple	*position(t_ray *ray, double distance)
{
	return (tpl_o(ray->o, *(scalar(ray->d, distance)), add));
}

t_tuple	*reflect(t_tuple in, t_tuple normal)
{
	return (tpl_o(in, *(scalar(normal, mul(dot_p(in, normal), 2))), sub));
}
