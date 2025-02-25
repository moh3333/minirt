/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:11:15 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/25 14:43:52 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_plane	*plane(int id, t_matrix *tr)
{
	t_plane	*pl;

	pl = ft_malloc(sizeof(t_plane), 0);
	pl->id = id;
	pl->material = material();
	pl->transform = tr;
	pl->inverse_m = inverse(tr);
	pl->transpose_inverse = transpose(pl->inverse_m);
	pl->normalv = cpv(0, 1, 0, 0);
	return (pl);
}
