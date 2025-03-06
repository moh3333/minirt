/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:15:01 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 21:47:09 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

void	print_error(char *error)
{
	int	i;

	i = 0;
	write (2, "Error\n", sizeof("Error\n"));
	while (error[i])
		write (2, &error[i++], 1);
	write (2, "\n", 1);
	exit(0);
}

void	*ft_malloc(size_t size, int flag)
{
	static char		bl[BLOCK_SIZE];
	static t_pool	head;
	void			*ret;

	if (flag == INIT)
		head.block = bl;
	if (head.offset + size > BLOCK_SIZE)
		return (print_error(MALLOC_FAILS), exit(0), NULL);
	ret = head.block + head.offset;
	head.offset += size;
	return (ret);
}
