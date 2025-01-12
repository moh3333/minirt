/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:35:04 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:37:43 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
	return (tpl_o(in, (scalar(normal, mul(Dot_p(in, normal), 2))), '-'));
}

double get_closest(double *t)
{
	if (t[0] < 0 && t[1] > 0)
		return (t[1]);
	else if (t[1] < 0 && t[0] > 0)
		return (t[0]);
	else if (t[0] > 0 && t[1] > 0)
	{
		if (t[0] < t[1])
			return (t[0]);
		else if (t[0] > t[1])
			return (t[1]);
		else if (t[0] == t[1])
			return (t[1]);
	}
	return (0);
}

t_material *material()
{
	t_material *mate = ft_malloc(sizeof(t_material));

	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	return (mate);
}