/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_intersection_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:31:21 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 15:05:06 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

static void	add_to_list(t_intersect **head, t_intersect *new)
{
	static t_intersect	*tmp;

	if (!*head)
	{
		*head = new;
		tmp = *head;
	}
	else
	{
		tmp->next = new;
		tmp = tmp->next;
	}
}

t_intersect	*world_intersection(t_world *world, t_ray *r)
{
	t_intersect	*head;
	t_intersect	*inter;
	int			i;


	i = 0;
	inter = NULL;
	head = NULL;
	while (i < world->object_count)
	{
		if (world->object[i].type == SPHER)
			inter = intersect(r, &world->object[i].shape);
		else if (world->object[i].type == PLANE)
			inter = pl_intersect(r, &world->object[i].shape_pl);
		else if (world->object[i].type == CYLINDER)
			inter = cyl_intersect(r, &world->object[i].shape_cyl);
		else if (world->object[i].type == CONE)
			inter = cone_intersect(r, &world->object[i].shape_co);
		if (inter)
			add_to_list(&head, inter);
		i++;
	}
	return (get_first_intersect(head, r));
}


