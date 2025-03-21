/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:25 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 21:57:47 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

void	check_file(char **bum, t_material *m)
{
	if (bum && ft_strcmp (bum[0], "texter") && bum[1])
	{
		if (m->texter)
			return (print_error(DOUBLE_TEX));
		m->texter = mlx_load_png (bum[1]);
		if (!m->texter)
			print_error(BAD_INFORM_SPH);
	}
	else if (bum && (ft_strcmp (bum[0], "bump") && bum[1]))
	{
		if (m->bump_map)
			return (print_error(DOUBLE_BUMP));
		m->bump_map = mlx_load_png(bum[1]);
		if (!m->bump_map)
			print_error(BAD_INFORM_SPH);
	}
	else
		return (print_error(BAD_PARAM_IN_FILE));
}

void	load_it(char **line, int i, t_material *m)
{
	char	**bum;

	if (ft_strstrlen (line) < i || !line[i])
		return ;
	bum = split_line (line[i], ':', ':');
	check_file (bum, m);
	if (ft_strstrlen(line) > i + 1)
	{
		bum = split_line (line[ft_strstrlen (line) - 1], ':', ':');
		check_file (bum, m);
	}
}

void	init_spher(char **line, t_rt *rt, int id)
{
	t_tuple		*crd;
	double		raduis;
	t_matrix	*tr;
	t_color		*col;
	int			len;

	len = ft_strstrlen(line);
	if (len != 4 && len != 5 && len != 6)
		return (print_error(BAD_INFORM_SPH));
	if (!is_float(line[2]))
		return (print_error(INVALID_SPHERE_RD));
	raduis = char_to_double(line[2]) / 2.0;
	if (raduis <= 0.0)
		return (print_error(INVALID_SPHERE_RD));
	crd = char_to_vec(line[1], 1);
	col = char_to_color(line[3]);
	rt->world->object[rt->world->object_count].type = SPHER;
	tr = mul_mat(transl_mat(crd->x, crd->y, crd->z), \
		scal_mat(raduis, raduis, raduis));
	rt->world->object[rt->world->object_count].shape = \
		*spher(cpv(0, 0, 0, 1), 1, id, tr);
	if (len > 4)
		additional_features(&rt->world->object[rt->world->object_count], line);
	rt->world->object[rt->world->object_count].shape.material->color = *col;
	rt->world->object_count++;
}

void	init_plane(char **line, t_rt *rt, int id)
{
	t_color		*col;
	t_tuple		*normal;
	t_tuple		*point;
	int			len;
	int			i;

	i = rt->world->object_count;
	len = ft_strstrlen(line);
	if (len != 4 && len != 6)
		return (print_error(BAD_INFORM_PL));
	col = char_to_color(line[3]);
	normal = char_to_vec(line[2], 0);
	check_normal_range(normal);
	normalize(normal);
	point = char_to_vec(line[1], 1);
	rt->world->object[i].type = PLANE;
	rt->world->object[i].shape_pl = *plane(id, mul_mat \
		(transl_mat(point->x, point->y, point->z), get_rotat_matrice(normal)));
	if (len == 6)
		init_checker(&rt->world->object[i], line[4], line[5]);
	rt->world->object[i].shape_pl.material->color = *col;
	rt->world->object_count++;
}
