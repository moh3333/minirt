/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:16:29 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/05 20:34:49 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt_utils.h"

t_matrix	*i_mat(double diagonal)
{
	t_matrix	*a;

	a = ft_malloc(sizeof(t_matrix), 0);
	a->matrix[0][0] = diagonal;
	a->matrix[0][1] = 0;
	a->matrix[0][2] = 0;
	a->matrix[0][3] = 0;
	a->matrix[1][1] = diagonal;
	a->matrix[1][0] = 0;
	a->matrix[1][2] = 0;
	a->matrix[1][3] = 0;
	a->matrix[2][2] = diagonal;
	a->matrix[2][0] = 0;
	a->matrix[2][1] = 0;
	a->matrix[2][3] = 0;
	a->matrix[3][3] = diagonal;
	a->matrix[3][0] = 0;
	a->matrix[3][1] = 0;
	a->matrix[3][2] = 0;
	return (a);
}

t_matrix	*transl_mat(double x, double y, double z)
{
	t_matrix	*ret;

	ret = i_mat(1.0);
	ret->matrix[0][3] = x;
	ret->matrix[1][3] = y;
	ret->matrix[2][3] = z;
	return (ret);
}

t_matrix	*scal_mat(double x, double y, double z)
{
	t_matrix	*ret;

	ret = i_mat(1.0);
	ret->matrix[0][0] = x;
	ret->matrix[1][1] = y;
	ret->matrix[2][2] = z;
	return (ret);
}

t_matrix	*transpose(t_matrix *a)
{
	t_matrix	*ret;
	int			i;
	int			j;

	i = -1;
	ret = i_mat(0.0);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[j][i] = a->matrix[i][j];
	}
	return (ret);
}
