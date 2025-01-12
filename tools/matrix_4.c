/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:23:35 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:42:37 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* get determinant of 2*2 matrix */

double det_2(t_2_2 *a)
{
	return(sub( mul(a->matrix[0][0], a->matrix[1][1]),\
		 mul(a->matrix[0][1], a->matrix[1][0])));
}

static void get_sub(double *a, double **d, int col)
{
	int p = 0;
	int s = 0;

	while (p < 4)
	{
		if (p == col && col < 3)
			p++;
		if (p == col && col == 3)
			break;
		(*d)[s] = a[p];
		s++;
		p++;
	}
}

/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */

t_3_3 *sub_m3(t_matrix *a, int row, int col)
{
	t_3_3 *d;
	int i, j;

	d = (t_3_3 *)ft_malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	d->matrix = new_3_3();
	i = 0;
	j = 0;
	while (i < 4)
	{
		if (i == row && row < 3)
			i++;
		if (i == row && row == 3)
			break;
		get_sub(a->matrix[i], &d->matrix[j], col);
		i++;
		j++;
	}
	return (d);
}