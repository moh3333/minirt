/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations_0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:07:45 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 22:19:24 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

double	dot_p(t_tuple a, t_tuple b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_tuple	*cross_p(t_tuple a, t_tuple b)
{
	return (cpv(((a.y * b.z) - (a.z * b.y)), \
	((a.z * b.x) - (a.x * b.z)), ((a.x * b.y) - (a.y * b.x)), 0));
}

double	radians(double degrees)
{
	return ((degrees / 180) * 3.14159265);
}

t_tuple	*scalar(t_tuple a, double scalar)
{
	return (cpv(mul(a.x, scalar), mul(a.y, scalar), mul(a.z, scalar), a.w));
}

double	magnitude(t_tuple a)
{
	return (sqrt((sq(a.x) + sq(a.y) + sq(a.z))));
}
