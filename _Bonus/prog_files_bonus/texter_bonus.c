/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:18:47 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 22:16:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

t_tuple	*normal_at(t_spher *sph, t_tuple *point)
{
	t_tuple	*object_p;
	t_tuple	*world_normal;

	object_p = tup_mat_mul(sph->inverse_m, point);
	if (sph->material->bump_map)
		bump_maping (sph->material, object_p, cpv(0, 0, 0, 0));
	world_normal = tup_mat_mul(sph->transpose_in, object_p);
	normalize(world_normal);
	world_normal->w = 0;
	return (world_normal);
}

void	bump_maping(t_material *m, t_tuple *n, t_tuple *pert)
{
	double		theta;
	double		phi;
	double		u;
	int			x;
	int			y;

	normalize(n);
	theta = atan2(n->z, n->x);
	phi = acos(n->y);
	x = (int) round((theta + M_PI) / (2.0 * M_PI) * (m->bump_map->width - 1));
	y = (int) round((1.0 - ((M_PI - phi) / M_PI)) * (m->bump_map->height - 1));
	u = (((m->bump_map->pixels[(y * m->bump_map->width + x) * 4] \
		/ 255.0)) * 2.0 - 1.0);
	pert = tpl_o(*scalar(*cpv(-sin(theta), 0, cos(theta), 0), u * 0.7), \
	*scalar(*cpv(cos(theta) * cos(phi), -sin(phi), \
		sin(theta) * cos(phi), 0), u * 0.7), add);
	n->x -= pert->x;
	n->y -= pert->y;
	normalize(n);
}

t_color	*spher_texter(t_spher *sp, t_material *m, t_comps *comp)
{
	t_tuple			*obj_point;
	int				x;
	int				y;
	unsigned char	*pixel;
	double			a[2];

	obj_point = tup_mat_mul(sp->inverse_m, comp->point);
	a[0] = (atan2(obj_point->z, obj_point->x) + M_PI) / (2.0 * M_PI);
	a[1] = (M_PI - acos(obj_point->y)) / M_PI;
	x = (int) round(a[0] \
		* (m->texter->width - 1));
	y = (int) round((1.0 - a[1]) * (m->texter->height - 1));
	pixel = &m->texter->pixels[(y * m->texter->width + x) * 4];
	return (new_color(pow(pixel[0] / 255.0, 2.2), \
		pow(pixel[1] / 255.0, 2.2), pow(pixel[2] / 255.0, 2.2)));
}

bool	spher_checker(t_spher *sp, t_comps *comp)
{
	t_tuple			*obj_point;
	int				arr[2];
	double			a[2];

	obj_point = tup_mat_mul(sp->inverse_m, comp->point);
	a[0] = (atan2(obj_point->z, obj_point->x) + M_PI) / (2.0 * M_PI);
	a[1] = (M_PI - acos(obj_point->y)) / M_PI;
	arr[0] = (int)floor(a[0] * sp->material->checker);
	arr[1] = (int)floor(a[1] * sp->material->checker);
	if ((arr[0] + arr[1]) % 2 == 0)
		return (true);
	return (false);
}
