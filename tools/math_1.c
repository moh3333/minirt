/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:00:52 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/18 16:00:15 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
/* get squar of a number */
double	sq(double num)
{
	return(pow(num, 2));
}

/* if "a" and "b" are vector the dot product is "a"."b" return a number 
wec need it to ompare the direction of the two vectors */
/* if the two vectors are unit theire dot product is actually the cosine of the ongle between them */
double	Dot_p(t_tuple *a, t_tuple *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

/* cross product if "a" and "b" are vector the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple *Cross_p(t_tuple *a, t_tuple *b)
{
	t_tuple *ret;

	ret = ft_malloc(sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = ((a->y * b->z) - (a->z * b->y));
	ret->y = ((a->z * b->x) - (a->x * b->z));
	ret->z = ((a->x * b->y) - (a->y * b->x));
	ret->w = 0;
	return (ret);
}

/* change from degrees to radians */
double radians(double degrees)
{
	return ((degrees / 180) * M_PI);
}