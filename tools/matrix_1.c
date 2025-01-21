/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:17:26 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 16:00:21 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* checks if two matrix are equals*/

int equal_mat(t_matrix *a, t_matrix *b)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (!isequal(a->matrix[i][j], b->matrix[i][j]))
				return (0);
		}
	}
	return (1);
}

/*helper function that help multiplying two matrixs */
static double	get(t_matrix *a, t_matrix *b, int row, int col)
{
	double result;
	int i;

	result = 0;
	i = -1;
	while (++i < 4)
		result += (a->matrix[row][i] * b->matrix[i][col]);
	return (result);
}
/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b)
{
	int i;
	int j;
	t_matrix *ret;

	i = -1; 
	ret = ft_malloc (sizeof(t_matrix));
	if (!ret)
		return (NULL);
	ret->matrix = new_4_4();
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = get(a, b, i, j);
	}
	return (ret);
}

/* multipling a matrix by  tuple creat another tuple */

t_tuple *tup_mat_mul(t_matrix *mtx, t_tuple *tpl)
{
	t_tuple *ret;
	t_tuple *tmp;
	double arr[4];
	int j;

	j = -1;
	while (++j < 4)
	{
		tmp = cpv(mtx->matrix[j][0], mtx->matrix[j][1],\
		mtx->matrix[j][2], mtx->matrix[j][3]);
		arr[j] = (tmp->x * tpl->x) + (tmp->y * tpl->y) + (tmp->z * tpl->z) + (tmp->w * tpl->w);
	}
	ret = cpv(arr[0], arr[1], arr[2], arr[3]);
	return (ret);
}
/*transpose take a matrix and change its rows to collomns and its collomns to rows */

t_matrix *transpose(t_matrix *a)
{
	t_matrix *ret;
	int i;
	int j;

	i = -1;
	ret = ft_malloc(sizeof(t_matrix));
	if (!ret)
		return (NULL);
	ret->matrix = new_4_4();
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[j][i] = a->matrix[i][j];
	}
	return (ret);
}