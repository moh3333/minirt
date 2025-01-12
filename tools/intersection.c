/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:38:30 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:38:56 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double hit(double *arr)
{
	if (arr[0] < 0 && arr[1] < 0)
		return (0);
	return (1);
}

double *intersections(int num, ...)
{
	va_list a;
	double *arr;
	int i;

	i = -1;
	arr = ft_malloc (num * sizeof(double));
	if (!arr)
		return (NULL);
	va_start(a, num);
	while (++i < num)
		arr[i] = va_arg(a, double);
	return (arr);
}

double ft_max(double *arr, int num)
{
	int i;
	double max;

	i = -1;
	max = -1;
	while (++i < num)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return (max);
}

double hit_p(double *arr, int num)
{
	int i;
	double min;

	i = -1;
	min = ft_max(arr, num);
	if (min < 0)
		return (-2147483648);
	if (min == 0)
		return (min);
	while (++i < num)
	{
		if (arr[i] < min)
			min = arr[i];
	}
	return (min);
}
