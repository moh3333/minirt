/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:58:15 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/19 16:04:17 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void *ft_malloc(size_t size)
{
	void *ret = malloc(size);
	bzero(ret, size);
	return (ret);
}

t_object *new_object()
{
	t_object *obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	return (obj);
}

t_comps *new_comps()
{
	t_comps *new;

	new = ft_malloc(sizeof(t_comps));
	if (!new)
		return (NULL);
	new->object = ft_malloc(sizeof(t_object));
	return (new);
}

double **new_2_2()
{
	double **ret;

	ret = ft_malloc(sizeof(double *) * 2);
	if (!ret)
		return (NULL);
	ret[0] = ft_malloc(sizeof(double ) * 2);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_malloc(sizeof(double ) * 2);
	if (!ret[1])
		return (NULL);
	return (ret);
}

double **new_3_3()
{
	double **ret;

	ret = ft_malloc(sizeof(double *) * 3);
	if (!ret)
		return (NULL);
	ret[0] = ft_malloc(sizeof(double ) * 3);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_malloc(sizeof(double ) * 3);
	if (!ret[1])
		return (NULL);
	ret[2] = ft_malloc(sizeof(double ) * 3);
	if (!ret[2])
		return (NULL);
	return (ret);
}

double **new_4_4()
{
	double **ret;

	ret = ft_malloc(sizeof(double *) * 4);
	if (!ret)
		return (NULL);
	ret[0] = ft_malloc(sizeof(double ) * 4);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_malloc(sizeof(double ) * 4);
	if (!ret[1])
		return (NULL);
	ret[2] = ft_malloc(sizeof(double ) * 4);
	if (!ret[2])
		return (NULL);
	ret[3] = ft_malloc(sizeof(double ) * 4);
	if (!ret[3])
		return (NULL);
	return (ret);
}

double *new_t(int count)
{
	double *ret = ft_malloc(sizeof(double ) * count);
	if(!ret)
		return (NULL);
	return (ret);
}

t_intersect *new_intersect()
{
	t_intersect *ret;

	ret = ft_malloc(sizeof(t_intersect));
	if (!ret)
		return (NULL);
	ret->t = new_t(2);
	ret->object = ft_malloc(sizeof(t_object));
	ret->next = NULL;
	return (ret);
}