/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:22:51 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:23:14 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

double	add(double a, double b)
{
	return (a + b);
}

/* subtract two floating point number */
double	sub(double a, double b)
{
	return (a - b);
}

/* multiply two floating point number */
double	mul(double a, double b)
{
	return (a * b);
}

/* divide two floating point number */
double	divi(double a, double b)
{
	return (a / b);
}

/* get squar of a number */
double	sq(double num)
{
	return (pow(num, 2));
}