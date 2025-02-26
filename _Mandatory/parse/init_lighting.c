/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lighting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:28:53 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:29:11 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_light(char **line, int exist, t_rt *rt)
{
	double	light_ratio;
	t_color	*light_col;
	t_tuple	*pos;

	if (exist)
		return (print_error(DUPLICAT_LIGHT));
	if (ft_strstrlen(line) != 3)
		return (print_error(BAD_INFORM_LIGHT));
	if (!is_float(line[2]))
		return (print_error(INVALID_LIGHT_N));
	pos = char_to_vec(line[1], 1);
	light_ratio = char_to_double(line[2]);
	if (!(light_ratio >= 0.0 && light_ratio <= 1.0))
		return (print_error(INVALID_LIGHT_R));
	light_col = new_color(light_ratio, light_ratio, light_ratio);
	rt->world->light[0] = *light_source(pos, light_col);
}
