/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:07:31 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:31:29 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_spher	*spher(t_tuple *center, double raduis, int id, t_matrix *tr)
{
	t_spher	*ret;

	ret = ft_malloc (sizeof(t_spher), 0);
	ret->c = center;
	ret->r = raduis;
	ret->id = id;
	ret->transform = tr;
	ret->material = material();
	ret->inverse_m = inverse(ret->transform);
	ret->transpose_in = transpose(ret->inverse_m);
	return (ret);
}

/* get the normal vector on a point on the spher*/
t_tuple	*normal_at(t_spher *sph, t_tuple *point)
{
	t_tuple	*object_p;
	t_tuple	*world_normal;

	object_p = tup_mat_mul(sph->inverse_m, point);
	world_normal = tup_mat_mul(sph->transpose_in, object_p);
	world_normal->w = 0;
	normalize(world_normal);
	return (world_normal);
}