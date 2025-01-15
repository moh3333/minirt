/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:39:01 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/15 16:27:48 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color *new_color(double r, double g, double b)
{
	t_color *col = ft_malloc(sizeof(t_color));
	col->r = r;
	col->g = g;
	col->b = b;
	return (col);
}

double get_col(t_color * color)
{
	double  col = 0;
	double r = color->r * 255;
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	double g = color->g * 255;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	double b = color->b * 255;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	col = ((uint64_t)r << 24) | ((uint64_t)g << 16) | ((uint64_t)b << 8) | 0xFF;
	return (col);
}
/* colors addition and subtraction */

t_color *colors_operation(t_color *a, t_color *b, char op)
{
	t_color *ret;
	double (*f) (double a, double b);

	f = NULL;
	if (op == '+')
		f = add;
	else if (op == '-')
		f = sub;
	else if (op == '*')
		f = mul;
	ret = ft_malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = f(a->r, b->r);
	ret->g = f(a->g, b->g);
	ret->b = f(a->b, b->b);
	return (ret);
}

/* colors multiplication with a scalar */

t_color *color_s_mul(t_color *a, double scalar)
{
	t_color *ret;

	ret = ft_malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = mul(a->r, scalar);
	ret->g = mul(a->g, scalar);
	ret->b = mul(a->b, scalar);
	return (ret);
}

/* get teh rgba format of a color from a number */

t_color *to_rgba(double color)
{
	t_color *ret = new_color(0.0,0.0,0.0);
	ret->r = ((uint64_t)color >> 16) & 255;
	ret->g = ((uint64_t)color >> 8) & 255;
	ret->b = ((uint64_t)color) & 255;
	return (ret);
}