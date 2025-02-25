/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:30:25 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/25 18:49:03 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"


void	init_spher(char **line, t_rt *rt, int id)
{
	t_tuple		*crd;
	double		raduis;
	t_matrix	*tr;
	t_color		*col;

	if (ft_strstrlen(line) != 4)
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
	rt->world->object[rt->world->object_count].shape.material->color = *col;
	rt->world->object_count++;
}

void	init_checker(t_plane *pl, char *scl, char *line)
{
	char **lines;

	lines = split_line(line, ':', ':');
	if (ft_strstrlen(lines) != 2)
		return (print_error(BAD_INFORM_PL_CK));
	pl->material->checker = char_to_double(scl);
	pl->material->pattern_color = *char_to_color(lines[1]);
}

void	init_plane(char **line, t_rt *rt, int id)
{
	t_color		*col;
	t_tuple		*normal;
	t_tuple		*point;
	int			len;

	len = ft_strstrlen(line);
	if (len != 4 && len != 6)
		return (print_error(BAD_INFORM_PL));
	col = char_to_color(line[3]);
	normal = char_to_vec(line[2], 0);
	normalize(normal);
	point = char_to_vec(line[1], 1);
	rt->world->object[rt->world->object_count].type = PLANE;
	rt->world->object[rt->world->object_count].shape_pl = *plane(id, \
	mul_mat(transl_mat(point->x, point->y, point->z), get_rotat_matrice(normal)));
	if (len == 6)
		init_checker(&rt->world->object[rt->world->object_count].shape_pl, line[4], line[5]);
	rt->world->object[rt->world->object_count].shape_pl.material->color = *col;
	rt->world->object_count++;
}

void	init_cylinder(char **line, t_rt *rt, int id)
{
	t_tuple		*centre;
	t_tuple		*normal;
	t_matrix	*tr;
	double		arr[4];
	t_color		*col;

	if (ft_strstrlen(line) != 6)
		return (print_error(INVALID_CYL_DATA));
	centre = char_to_vec(line[1], 1);
	normal = char_to_vec(line[2], 0);
	normalize(normal);
	if (!is_float(line[3]) || !is_float(line[4]))
		return (print_error(INVALID_CYL_D_H));
	arr[0] = char_to_double(line[3]) / 2.0;
	arr[1] = char_to_double(line[4]) / 2.0;
	if (!(arr[0] >= 0 && arr[0] <= INT_MAX) || !(arr[0] >= 0 && arr[0] <= INT_MAX))
		return (print_error(INVALID_CYL_D_H));
	arr[2] = -arr[1];
	arr[3] = arr[1];
	col = char_to_color(line[5]);
	rt->world->object[rt->world->object_count].type = CYLINDER;
	tr = mul_mat(mul_mat(transl_mat(centre->x, centre->y, centre->z), get_rotat_matrice(normal)), scal_mat(arr[0], 1, arr[0]));
	rt->world->object[rt->world->object_count].shape_cyl = \
		*cylinder((arr + 2), id, tr);
	rt->world->object[rt->world->object_count].shape_cyl.material->color = *col;
	rt->world->object_count++;
}

void init_cone(char **line, t_rt *rt, int id)
{

	t_tuple		*centre;
	t_tuple		*normal;
	t_matrix	*tr;
	double		arr[4];
	t_color		*col;

	if (ft_strstrlen(line) != 6)
		return (print_error(INVALID_CO_DATA));
	centre = char_to_vec(line[1], 1);
	normal = char_to_vec(line[2], 0);
	normalize(normal);
	if (!is_float(line[3]) || !is_float(line[4]))
		return (print_error(INVALID_CO_DATA));
	arr[0] = char_to_double(line[3]) / 2.0 ;
	arr[1] = char_to_double(line[4]) / 2.0;
	if (!(arr[0] >= 0 && arr[0] <= INT_MAX) || !(arr[0] >= 0 && arr[0] <= INT_MAX))
		return (print_error(INVALID_CO_D_H));
	arr[2] = -arr[1] ;
	arr[3] = arr[1] ;
	col = char_to_color(line[5]);
	rt->world->object[rt->world->object_count].type = CONE;
	tr = mul_mat(mul_mat(transl_mat(centre->x, centre->y+ arr[1]/2.0, centre->z), get_rotat_matrice(normal)), scal_mat(arr[0]/arr[1],2, arr[0]/arr[1]));
	rt->world->object[rt->world->object_count].shape_co = \
		*cone((arr + 2), id, tr);
	rt->world->object[rt->world->object_count].shape_co.material->color = *col;
	rt->world->object_count++;
}