/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:55:52 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:02:30 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minirt.h"

/* compare two floating point number we use a constant  */
int isequal(double a, double b)
{
	return ((fabs(a-b) < EPSILON));
}
/* add two floating point number */
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