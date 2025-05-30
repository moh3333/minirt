/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ambiant_cam_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:40:24 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 00:32:23 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

void	init_ambiant(char **line, int exist, t_rt *rt)
{
	double	amb_ratio;
	t_color	*ambiant;

	if (exist)
		return (print_error(DUPLICAT_AMB));
	if (ft_strstrlen(line) != 3)
		return (print_error(BAD_INFORM_AMB));
	if (!is_float(line[1]))
		return (print_error(INVALID_AMB_N));
	amb_ratio = char_to_double(line[1]);
	if (!(amb_ratio >= 0.0 && amb_ratio <= 1.0))
		return (print_error(INVALID_AMB_R));
	ambiant = char_to_color(line[2]);
	rt->world->ambiant_color = color_s_mul(ambiant, amb_ratio);
}

void	init_camera(char **line, int exist, t_rt *rt)
{
	double	fov;
	t_tuple	*vec;
	t_tuple	*ori;

	if (exist)
		return (print_error(DUPLICAT_CAM));
	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_CAM));
	if (!is_float(line[3]))
		return (print_error(INVALID_FOV));
	vec = char_to_vec(line[2], 1);
	check_normal_range(vec);
	normalize(vec);
	fov = char_to_double(line[3]);
	ori = char_to_vec(line[1], 1);
	if ((fov < 0.0 || fov > 180.0))
		return (print_error(INVALID_FOV));
	rt->cam = new_camera(HIGHT, WIDTH, radians(fov), \
		view_transformation (ori, vec, cpv(0, 1, 0, 0)));
	rt->cam->origine = ori;
}
