/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:13:12 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 20:37:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

void	check_extension(char *file_name)
{
	int	i;

	i = 0;
	if (ft_strlen(file_name) < 4)
		return (print_error(VALID_NAME));
	while (file_name[i])
		i++;
	if (!(file_name[i - 1] == 't' \
		&& file_name[i - 2] == 'r' && file_name[i - 3] == '.'))
		return (print_error(VALID_NAME));
}

t_line	*parse_file(char *file_name)
{
	int		fd;
	t_line	*l;

	check_extension(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILS), NULL);
	l = get_rt_lines(fd);
	close(fd);
	return (l);
}

t_line	*get_rt_lines(int fd)
{
	int		i;
	t_line	*l;

	i = 0;
	l = ft_malloc(sizeof(t_line), 0);
	while (i < 199)
	{
		l->line[i] = get_next_line(fd);
		if (!l->line[i])
			break ;
		i++;
	}
	l->count = i;
	return (l);
}
