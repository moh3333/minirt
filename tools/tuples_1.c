/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:07:25 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 18:12:42 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a)
{
	return (sqrt((sq(a->x) + sq(a->y) + sq(a->z))));
}

/* check if its a unit vector */
double	isunit(t_tuple *a)
{
	return ((magnitude(a) == 1));
}

/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
t_tuple *Normalize(t_tuple *a)
{
	t_tuple *ret;
	double v;

	ret = ft_malloc (sizeof (t_tuple));
	if (!ret)
		return (NULL);
	v = magnitude(a);
	if (!v)
		return (a);
	ret->x = (a->x / v);
	ret->y = (a->y / v);
	ret->z = (a->z / v);
	ret->w = a->w;
	return (ret);
}

/* creat a ray with origine and direction */
t_ray *ray(t_tuple *origine, t_tuple *direction)
{
	t_ray *ret;

	ret = ft_malloc (sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->o = origine;
	ret->d = direction;
	return (ret);
}

/*get the position of a point in a ray */
t_tuple *position(t_ray *ray, double distance)
{
	return (tpl_o(ray->o , scalar(ray->d, distance), '+'));
}