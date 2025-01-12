/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:22:36 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:42:21 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* submatrix 2*2 remove a collamn and a row from a 3*3 matrix */

t_2_2 *sub_m2(t_3_3 *a, int row, int col)
{
	t_2_2 *d;
	int i[4];

	d = (t_2_2 *)ft_malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	d->matrix = new_2_2();
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
			d->matrix[i[2]][i[3]] = a->matrix[i[0]][i[1]] ;
			i[1]++;
			i[3]++;
		}
		i[0]++;
		i[2]++;
	}
	return (d);
}

/* is the determinant of a 3*3 submatrix after removing a row and col */

double	ft_minor(t_3_3 *a, int row, int col)
{
	return (det_2(sub_m2(a, row, col)));
}

/* get the cofactor sign depending on the case the row and col removed share in the matrix */

double cof_sign(int r, int c)
{
	if ((!(r % 2) && (c % 2)) || ((r % 2) && (!(c % 2))))
		return (-1);
	return (1);
}

/* gettin the cofactor of the 3*3 matrix */

double cof_3(t_3_3 *a, int row , int col )
{
	return ((ft_minor(a, row , col) * cof_sign(row, col)));
}