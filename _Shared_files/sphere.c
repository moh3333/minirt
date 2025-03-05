/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:07:31 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/02 21:33:01 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_spher	*spher(t_tuple *center, double raduis, int id, t_matrix *tr)
{
	t_spher	*ret;

	ret = ft_malloc (sizeof(t_spher), 0);
	ret->c = center;
	ret->r = raduis;
	ret->id = id;
	ret->transform = tr;
	ret->material = material();
	ret->inverse_m = inverse(ret->transform);
	ret->transpose_in = transpose(ret->inverse_m);
	return (ret);
}
