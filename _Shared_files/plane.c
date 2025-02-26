/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:09:43 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:10:10 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_plane	*plane(int id, t_matrix *tr)
{
	t_plane	*pl;

	pl = ft_malloc(sizeof(t_plane), 0);
	pl->id = id;
	pl->material = material();
	pl->transform = tr;
	pl->inverse_m = inverse(tr);
	pl->transpose_inverse = transpose(pl->inverse_m);
	pl->normalv = cpv(0,1,0,0);
	return (pl);
}