/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:09:00 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 17:22:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_ray	*ray(t_tuple origine, t_tuple direction)
{
	t_ray	*ret;

	ret = ft_malloc (sizeof(t_ray), 0);
	ret->o = origine;
	ret->d = direction;
	return (ret);
}

t_ray	*transform(t_ray *t, t_matrix *mat)
{
	return (ray(*tup_mat_mul(mat, &t->o), *tup_mat_mul(mat, &t->d)));
}

t_ray	*ray_for_pixel(t_camera *cam, double x, double y)
{
	t_tuple	*direction;
	double	x_offset;
	double	y_offset;
	double	world_x;
	double	world_y;

	x_offset = (x + 0.5) * cam->pixel_size;
	y_offset = (y + 0.5) * cam->pixel_size;
	world_x = cam->half_width - x_offset;
	world_y = cam->half_hight - y_offset;
	direction = tpl_o(*tup_mat_mul(cam->transform_inverse, \
				cpv(world_x, world_y, -1, 1)), *cam->origine, sub);
	return (normalize(direction), ray(*cam->origine, *direction));
}
