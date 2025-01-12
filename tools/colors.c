/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:39:01 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:39:46 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	else if (op == '/')
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