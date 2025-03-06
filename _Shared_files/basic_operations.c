/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:22:51 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 20:30:38 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

double	add(double a, double b)
{
	return (a + b);
}

double	sub(double a, double b)
{
	return (a - b);
}

double	mul(double a, double b)
{
	return (a * b);
}

double	divi(double a, double b)
{
	return (a / b);
}

double	sq(double num)
{
	return (pow(num, 2));
}
