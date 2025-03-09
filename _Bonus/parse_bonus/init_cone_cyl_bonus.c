/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone_cyl_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:23:19 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 20:30:39 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

static void	init_cone_cyl(double arr[4], char **line, t_color **col)
{
	arr[0] = char_to_double(line[3]) / 2.0 ;
	arr[1] = char_to_double(line[4]) / 2.0;
	if (!(arr[0] >= 0 && arr[0] <= INT_MAX) \
			|| !(arr[0] >= 0 && arr[0] <= INT_MAX))
		return (print_error(INVALID_CO_D_H));
	arr[2] = -arr[1];
	arr[3] = arr[1];
	*col = char_to_color(line[5]);
}

void	init_cylinder(char **line, t_rt *rt, int id)
{
	t_tuple		*centre;
	t_tuple		*normal;
	t_matrix	*tr;
	double		arr[4];
	t_color		*col;

	col = NULL;
	if (ft_strstrlen(line) != 6)
		return (print_error(INVALID_CYL_DATA));
	centre = char_to_vec(line[1], 1);
	normal = char_to_vec(line[2], 0);
	check_normal_range(normal);
	normalize(normal);
	if (!is_float(line[3]) || !is_float(line[4]))
		return (print_error(INVALID_CYL_D_H));
	init_cone_cyl(arr, line, &col);
	rt->world->object[rt->world->object_count].type = CYLINDER;
	tr = mul_mat(mul_mat(transl_mat(centre->x, centre->y, centre->z), \
	get_rotat_matrice(normal)), scal_mat(arr[0], 1, arr[0]));
	rt->world->object[rt->world->object_count].shape_cyl = \
		*cylinder((arr + 2), id, tr);
	rt->world->object[rt->world->object_count].shape_cyl.material->color = *col;
	rt->world->object_count++;
}

void	init_cone(char **line, t_rt *rt, int id)
{
	t_tuple		*centre;
	t_tuple		*normal;
	t_matrix	*tr;
	double		arr[4];
	t_color		*col;

	col = NULL;
	if (ft_strstrlen(line) != 6)
		return (print_error(INVALID_CO_DATA));
	centre = char_to_vec(line[1], 1);
	normal = char_to_vec(line[2], 0);
	check_normal_range(normal);
	normalize(normal);
	if (!is_float(line[3]) || !is_float(line[4]))
		return (print_error(INVALID_CO_DATA));
	init_cone_cyl(arr, line, &col);
	rt->world->object[rt->world->object_count].type = CONE;
	tr = mul_mat(mul_mat(transl_mat(centre->x, centre->y, \
		centre->z), get_rotat_matrice(normal)), \
			scal_mat(arr[0] / arr[1], 1, arr[0] / arr[1]));
	rt->world->object[rt->world->object_count].shape_co = \
		*cone((arr + 2), id, tr);
	rt->world->object[rt->world->object_count].shape_co.material->color = *col;
	rt->world->object_count++;
}
