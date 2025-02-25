/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:28:53 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/25 19:29:43 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

void	init_light(char **line, t_rt *rt)
{
	double	light_ratio;
	t_color	*light_col;
	t_tuple	*pos;

	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_LIGHT));
	if (!is_float(line[2]))
		return (print_error(INVALID_LIGHT_N));
	pos = char_to_vec(line[1], 1);
	light_ratio = char_to_double(line[2]);
	if (!(light_ratio >= 0.0 && light_ratio <= 1.0))
		return (print_error(INVALID_LIGHT_R));
	light_col = char_to_color(line[3]);
	rt->world->light[rt->world->light_count] = *light_source(pos, color_s_mul(light_col, light_ratio));
	rt->world->light_count++;
}

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
