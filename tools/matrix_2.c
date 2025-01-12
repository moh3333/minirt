/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:20:02 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:42:09 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*getting the determinant of the 3*3 matrix u have the choice to work with the cols o rows
u will get the same  result  */
double det_3(t_3_3 *a)
{
	return ((cof_3(a, 0, 0) * a->matrix[0][0]) + \
		(cof_3(a, 0, 1) * a->matrix[0][1]) + \
		(cof_3(a, 0, 2) * a->matrix[0][2]));
}

double	cofactor(t_matrix *a, int row , int col)
{
	t_3_3 *sub = sub_m3(a, row, col);
	return ((det_3(sub)) * cof_sign(row, col));
}

double determinant(t_matrix *a)
{
	return ((cofactor(a, 0, 0) * a->matrix[0][0]) + \
		(cofactor(a, 0, 1) * a->matrix[0][1]) + \
		(cofactor(a, 0, 2) * a->matrix[0][2]) + \
		(cofactor(a, 0, 3) * a->matrix[0][3]));
}

/*checks the matrix inverbility is it return 0 mean thats not invertible */
double invertible(t_matrix *a)
{
	return (determinant(a));
}

/* get th inverse of a matrix */
t_matrix *inverse(t_matrix *a)
{
	t_matrix *ret;
	int i;
	int j;
	double det;

	if (!invertible(a))
		return (a);
	det = determinant(a);
	ret = ft_malloc(sizeof(t_matrix));
	if (!ret)
		return (NULL);
	ret->matrix = new_4_4();
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = (cofactor(a, i, j) / det);
	}
	return (transpose(ret));
}