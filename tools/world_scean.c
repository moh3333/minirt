/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_scean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:46:02 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/18 16:01:49 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_world *world()
{
	t_world *world;

	world = ft_malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	return (world);
}

t_intersect *world_intersect(t_world *w, t_ray *r)
{
	int i;
	t_intersect *inter;
	t_intersect *f[200];
	
	inter->ray = r;
	inter = ft_malloc(sizeof(t_intersect));
	while (i < w->object_count)
	{
		if (w->object[i].type == SPHER){
			f[i] = intersect(r, w->object[i].shape)
			if (f[i])
				count += 
		}
	}
	return (inter)
}