/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:17:11 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 20:34:18 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_2_2	*sub_m2(t_3_3 *a, int row, int col)
{
	t_2_2	*d;
	int		i[4];

	d = ft_malloc (sizeof(t_3_3), 0);
	i[0] = 0;
	i[2] = 0;
	while ((i[0]) < 3 && (i[2]) < 2)
	{
		if (i[0] == row)
			++(i[0]);
		i[1] = 0;
		i[3] = 0;
		while ((i[1]) < 3 && (i[3]) < 2)
		{
			if (i[1] == col)
				++(i[1]);
			d->matrix[i[2]][i[3]] = a->matrix[i[0]][i[1]];
			i[1]++;
			i[3]++;
		}
		i[0]++;
		i[2]++;
	}
	return (d);
}

double	det_2(t_2_2 *a)
{
	return (sub(mul(a->matrix[0][0], a->matrix[1][1]), \
		mul(a->matrix[0][1], a->matrix[1][0])));
}
