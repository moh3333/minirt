/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:57:08 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/08 13:13:07 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

/* identity matrix multipliyng by any matrix it gives the same matrix */
t_matrix	*i_mat(void)
{
	t_matrix	*a;

	a = ft_malloc(sizeof(t_matrix), 0);
	a->matrix[0][0] = 1;
	a->matrix[1][1] = 1;
	a->matrix[2][2] = 1;
	a->matrix[3][3] = 1;
	return (a);
}

/* get the translation matrix we need to translate a point */
t_matrix	*transl_mat(double x, double y, double z)
{
	t_matrix	*ret;

	ret = i_mat();
	ret->matrix[0][3] = x;
	ret->matrix[1][3] = y;
	ret->matrix[2][3] = z;
	return (ret);
}

/* get the scalling matrix */
t_matrix	*scal_mat(double x, double y, double z)
{
	t_matrix	*ret;

	ret = i_mat();
	ret->matrix[0][0] = x;
	ret->matrix[1][1] = y;
	ret->matrix[2][2] = z;
	return (ret);
}

/* rotat a vector or a point to an axis x y or z */
t_matrix	*rotat_matrix(double radians, char axis)
{
	t_matrix	*ret;
	int			r[2];

	r[0] = 0;
	r[1] = 0;
	ret = i_mat();
	if (axis == 'x' && ++(r[0]) && ++(r[0]) && ++(r[1]))
		;
	else if (axis == 'y' && ++(r[1]) && ++(r[1]))
		;
	else if (axis == 'z' && ++(r[1]))
		;
	ret->matrix[r[0]][r[0]] = cos(radians);
	ret->matrix[r[1]][r[1]] = ret->matrix[r[0]][r[0]];
	if (axis == 'z')
	{
		ret->matrix[r[1]][r[0]] = sin(radians);
		ret->matrix[r[0]][r[1]] = -(ret->matrix[r[1]][r[0]]);
	}
	else
	{
		ret->matrix[r[0]][r[1]] = sin(radians);
		ret->matrix[r[1]][r[0]] = -(ret->matrix[r[0]][r[1]]);
	}
	return (ret);
}

/*transpose take a matrix and change 
its rows to collomns and its collomns to rows */
t_matrix	*transpose(t_matrix *a)
{
	t_matrix	*ret;
	int			i;
	int			j;

	i = -1;
	ret = ft_malloc(sizeof(t_matrix), 0);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[j][i] = a->matrix[i][j];
	}
	return (ret);
}
