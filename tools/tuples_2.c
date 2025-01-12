/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:15:55 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:29:21 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* translate  point */
t_tuple *transl(t_tuple *point, t_matrix *tr_mtx)
{
	return (tup_mat_mul(tr_mtx, point));
}

/* scall point */
t_tuple *scall(t_tuple *point, t_matrix *scal_mtx)
{
	return (tup_mat_mul(scal_mtx, point));
}

/* transform a ray */
t_ray *transform(t_ray *t, t_matrix *mat)
{
	t_ray *ra;

	ra = ft_malloc(sizeof(t_ray));
	if (!ra)
		return (NULL);
	ra->o = tup_mat_mul(mat, t->o);
	ra->d = tup_mat_mul(mat , t->d);
	ra->ud = Normalize(ra->d);
	return (ra);
}
