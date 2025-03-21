/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:21:35 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 22:04:36 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_color	*new_color(double r, double g, double b)
{
	t_color	*col;

	col = ft_malloc(sizeof(t_color), 0);
	col->r = fmax(0.0, fmin(1.0, r));
	col->g = fmax(0.0, fmin(1.0, g));
	col->b = fmax(0.0, fmin(1.0, b));
	return (col);
}

uint64_t	get_col(t_color *color)
{
	uint64_t	r;
	uint64_t	g;
	uint64_t	b;

	r = fmax(0.0, fmin(255.0, color->r * 255.0));
	g = fmax(0.0, fmin(255.0, color->g * 255.0));
	b = fmax(0.0, fmin(255.0, color->b * 255.0));
	return (((uint64_t)r << 24) | \
		((uint64_t)g << 16) | ((uint64_t)b << 8) | 0xFF);
}

t_color	*colors_operation(t_color *a, t_color *b, \
	double (*f) (double a, double b))
{
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (!a && !b)
		return (new_color(0, 0, 0));
	return (new_color(f(a->r, b->r), f(a->g, b->g), f(a->b, b->b)));
}

t_color	*color_s_mul(t_color *a, double scalar)
{
	return (new_color(mul(a->r, scalar), mul(a->g, scalar), mul(a->b, scalar)));
}

t_color	*to_rgba(double color)
{
	return (new_color((((uint64_t)color >> 16) & 0xFF) / 255.0, \
		(((uint64_t)color >> 8) & 0xFF) / 255.0, \
		(((uint64_t)color) & 0xFF) / 255.0));
}
