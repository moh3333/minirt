/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:18:24 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 20:33:35 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_matrix	*inverse(t_matrix *a)
{
	t_matrix	*ret;
	int			i;
	int			j;
	double		det;

	det = determinant(a);
	if (!det)
		return (a);
	ret = i_mat(0.0);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = (cofactor(a, i, j) / det);
	}
	return (transpose(ret));
}

double	determinant(t_matrix *a)
{
	return ((cofactor(a, 0, 0) * a->matrix[0][0]) + \
		(cofactor(a, 0, 1) * a->matrix[0][1]) + \
		(cofactor(a, 0, 2) * a->matrix[0][2]) + \
		(cofactor(a, 0, 3) * a->matrix[0][3]));
}

double	cofactor(t_matrix *a, int row, int col)
{
	return ((det_3(sub_m3(a, row, col))) * cof_sign(row, col));
}

/*getting the determinant of the 3*3 matrix 
u have the choice to work with the cols o rows
u will get the same  result  */
double	det_3(t_3_3 *a)
{
	return ((cof_3(a, 0, 0) * a->matrix[0][0]) + \
		(cof_3(a, 0, 1) * a->matrix[0][1]) + \
		(cof_3(a, 0, 2) * a->matrix[0][2]));
}
