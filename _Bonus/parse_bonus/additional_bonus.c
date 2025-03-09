/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:57:59 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 21:58:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

void	init_checker(t_object *o, char *scl, char *line)
{
	char	**lines;
	t_plane	*pl;
	t_spher	*sp;

	if (o->type == PLANE)
	{
		pl = &o->shape_pl;
		lines = split_line(line, ':', ':');
		if (ft_strstrlen(lines) != 2)
			return (print_error(BAD_INFORM_PL_CK));
		pl->material->checker = char_to_double(scl);
		pl->material->pattern_color = *char_to_color(lines[1]);
	}
	else if (o->type == SPHER)
	{
		sp = &o->shape;
		lines = split_line(line, ':', ':');
		if (ft_strstrlen(lines) != 2)
			return (print_error(BAD_INFORM_SP_CK));
		sp->material->checker = char_to_double(scl);
		sp->material->pattern_color = *char_to_color(lines[1]);
	}
}

void	additional_features(t_object *obj, char **line)
{
	if (line[4][0] >= '0' && line[4][0] <= '9')
		init_checker(obj, line[4], line[5]);
	else if (line[4][0] == 't' || line[4][0] == 'b')
		load_it(line, 4, obj->shape.material);
	else
		return (print_error(UKNOWN));
}
