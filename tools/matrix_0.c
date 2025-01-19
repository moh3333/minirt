/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:12:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/16 14:21:33 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* identity matrix multipliyng by any matrix it gives the same matrix */

t_matrix *i_mat(void)
{
	int i;
	int j;
	t_matrix *a;

	i = -1;
	a = ft_malloc(sizeof(t_matrix));
	if (!a)
		return (NULL);
	a->matrix = new_4_4();
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				a->matrix[i][j] = 1;
			else
				a->matrix[i][j] = 0;
		}
	}
	return (a);
}

/* get the translation matrix we need to translate a point */

t_matrix *transl_mat(double x, double y, double z)
{
	t_matrix *ret;

	ret = i_mat();
	ret->matrix[0][3] = x;
	ret->matrix[1][3] = y;
	ret->matrix[2][3] = z;
	return (ret);
}

/* get the scalling matrix */
t_matrix *scal_mat(double x, double y, double z)
{
	t_matrix *ret;

	ret = i_mat();
	ret->matrix[0][0] = x;
	ret->matrix[1][1] = y;
	ret->matrix[2][2] = z;
	return (ret);
}

/* rotat a vector or a point to an axis x y or z */
t_matrix *rotat_matrix(double radians, char axis)
{
	t_matrix *ret;
	int r[2];

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

/* get the skewing (shearing matrix) */
t_matrix *skew_mat(double *arr)
{
	t_matrix *ret;

	ret = i_mat();
	ret->matrix[0][1] = arr[0];
	ret->matrix[0][2] = arr[1];
	ret->matrix[1][0] = arr[2];
	ret->matrix[1][2] = arr[3];
	ret->matrix[2][0] = arr[4];
	ret->matrix[2][1] = arr[5];
	return (ret);
}