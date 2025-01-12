/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:58:15 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:11:25 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void *ft_malloc(size_t size)
{
	void *ret = malloc(size);
	bzero(ret, size);
	return (ret);
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

double *new_t()
{
	double *ret = ft_malloc(sizeof(double ) * 2);
	if(!ret)
		return (NULL);
	return (ret);
}