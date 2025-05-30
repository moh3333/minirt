/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identfier_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:27:52 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/09 22:16:36 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

void	parse_init_structs(t_line *l, t_rt *rt)
{
	int		i;
	char	**line;

	i = 0;
	while (i < l->count)
	{
		line = split_line(l->line[i], 32, 9);
		if (line && line[0])
			init_struct(line, rt);
		i++;
	}
}

void	init_struct(char **line, t_rt *rt)
{
	static int	check_identifier[2];
	int			i;

	i = 0;
	if (ft_strcmp(line[0], "C"))
	{
		init_camera(line, check_identifier[0], rt);
		(check_identifier[0])++;
	}
	else if (ft_strcmp(line[0], "A"))
	{
		init_ambiant(line, check_identifier[1], rt);
		(check_identifier[1])++;
	}
	else if (ft_strcmp(line[0], "L"))
		init_light(line, rt);
	else
		init_objects(line, rt);
}

void	init_objects(char **line, t_rt *rt)
{
	static int	arr[4];

	if (ft_strcmp("sp", line[0]))
	{
		init_spher(line, rt, arr[0]);
		(arr[0])++;
	}
	else if (ft_strcmp("pl", line[0]))
	{
		init_plane(line, rt, arr[1]);
		(arr[1])++;
	}
	else if (ft_strcmp("cy", line[0]))
	{
		init_cylinder(line, rt, arr[2]);
		(arr[2])++;
	}
	else if (ft_strcmp("co", line[0]))
	{
		init_cone(line, rt, arr[3]);
		(arr[3])++;
	}
	else
		return (print_error(INDEFINED_OBJECT));
}
