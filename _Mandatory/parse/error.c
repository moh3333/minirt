/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:31:41 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/08 13:19:35 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	print_error(char *error)
{
	int	i;

	i = 0;
	write (2, "Error\n", sizeof("Error\n"));
	while (error[i])
		write (2, &error[i++], 1);
	write (2, "\n", 1);
	ft_malloc(0, FREE);
}

void	ft_free(t_leaks **list)
{
	t_leaks	*head;
	t_leaks	*tmp;

	head = *list;
	tmp = NULL;
	while (head && head->node)
	{
		tmp = head;
		head = head->next;
		free(tmp->node);
		free(tmp);
	}
	exit(1);
}

void	*ft_malloc(size_t size, int flag)
{
	static t_leaks	*head;
	static t_leaks	*tail;
	t_leaks			*tmp;
	void			*ret;

	if (flag == FREE)
		ft_free(&head);
	ret = calloc(size, 1);
	if (!ret)
		return (print_error(MALLOC_FAILS), ft_malloc(0, FREE), NULL);
	if (!head)
	{
		head = calloc (sizeof(t_leaks), 1);
		head->node = ret;
		tail = head;
	}
	else
	{
		tail->next = calloc (sizeof(t_leaks), 1);
		tail->next->node = ret;
		tail = tail->next;
	}
	return (ret);
}
