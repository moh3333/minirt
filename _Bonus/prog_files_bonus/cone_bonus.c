/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:43:18 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 17:24:52 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

t_cone	*cone(double *trunc, int id, t_matrix *tr)
{
	t_cone	*co;

	co = ft_malloc(sizeof(t_cone), 0);
	co->id = id;
	co->min = trunc[0];
	co->max = trunc[1];
	co->material = material();
	co->transform = tr;
	co->inverse_m = inverse(tr);
	co->transpose_inverse = transpose(co->inverse_m);
	return (co);
}

t_tuple	*normal_at_co(t_cone *co, t_tuple *p_)
{
	t_tuple	*n_obj_space;
	t_tuple	*p;
	double	dist;
	t_tuple	*n_world_space;

	dist = 0;
	n_obj_space = NULL;
	p = tup_mat_mul(co->inverse_m, p_);
	if (p->y > EPSILON)
		p->y = -p->y;
	n_obj_space = cpv(p->x, -sqrt(sq(p->x) + sq(p->z)), p->z, 0);
	dist = sqrt(sq(p->x) + sq(p->z));
	if (dist < 1.0 && p->y >= (co->max - EPSILON))
		ch_pv(n_obj_space, 0, 1, 0);
	else if (dist < 1.0 && p->y <= (co->min + EPSILON))
		ch_pv(n_obj_space, 0, -1, 0);
	n_world_space = tup_mat_mul(co->transpose_inverse, n_obj_space);
	normalize(n_world_space);
	return (n_world_space);
}
