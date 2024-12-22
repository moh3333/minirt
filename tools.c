/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2024/12/22 11:55:27 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*if p_v is (1) creat point if its 0 creat vector */

t_tuple *cpv(double x, double y, double z, int p_v)
{
	t_tuple *a;

	a = malloc(sizeof(t_tuple));
	if (!a)
		return (NULL);
	a->x = x;
	a->y = y;
	a->z = z;
	a->w = p_v;
	return (a);
}

/* if it return (0) it's a point else it's a vector */
int ispoint(t_tuple *a)
{
	return ((a->w == 1));
}

/* compare two floating point number we use a constant  */
int equal(double a, double b)
{
	return ((fabs(a-b) < EPSILON));
}
/* add two floating point number */
double	add(double a, double b)
{
	return (a + b);
}

/* subtract two floating point number */
double	sub(double a, double b)
{
	return (a - b);
}

/* multiply two floating point number */
double	mul(double a, double b)
{
	return (a * b);
}

/* divide two floating point number */
double	div(double a, double b)
{
	return (a / b);
}

/*operation two tuples */
t_tuple *tpl_o(t_tuple *a, t_tuple *b , char op)
{
	t_tuple *ret;
	double	(*f)(double p1, double p2);

	if(op == '+')
		f = add;
	else if(op == '-')
		f = sub;
	ret = malloc (sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = f(a->x, b->x);
	ret->y = f(a->y, b->y);
	ret->z = f(a->z, b->z);
	ret->w = f(a->w, b->w);
	return (ret);
}
/*get the opposite vector if the given is from a to b it will return the vector from b to a */
t_tuple *opp(t_tuple *a)
{
	t_tuple *opp;

	opp = malloc (sizeof (t_tuple));
	if (!opp)
		return (NULL);
	opp->x = -a->x;
	opp->y = -a->y;
	opp->z = -a->z;
	opp->w = -a->w;
	return (opp);
}
/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple *a, double scalar)
{
	t_tuple *ret;

	ret = malloc(sizeof (t_tuple));
	if (!ret)
		return (NULL);
	ret->x = (mul(a->x, scalar));
	ret->y = (mul(a->y, scalar));
	ret->z = (mul(a->z, scalar));
	ret->w = (mul(a->w, scalar));
	return (ret);
}

/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a)
{
	return (sqrt((pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2))));
}

/* check if its a unit vector */
double	isunit(t_tuple *a)
{
	return ((magnitude(a) == 1));
}

/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
t_tuple *Normalize(t_tuple *a)
{
	t_tuple *ret;
	double v;

	ret = malloc (sizeof (t_tuple));
	if (!ret)
		return (NULL);
	v = magnitude(a);
	if (!v)
		return (a);
	ret->x = (a->x / v);
	ret->y = (a->y / v);
	ret->z = (a->z / v);
	ret->w = a->w;
	return (ret);
}
/* if "a" and "b" are vector the dot product is "a"."b" return a number 
wec need it to ompare the direction of the two vectors */
/* if the two vectors are unit theire dot product is actually the cosine of the ongle between them */
double	Dot_p(t_tuple *a, t_tuple *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w));
}

/* cross product if "a" and "b" are vector the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple *Cross_p(t_tuple *a, t_tuple *b)
{
	t_tuple *ret;

	ret = malloc(sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = ((a->y * b->z) - (a->z * b->y));
	ret->y = ((a->z * b->x) - (a->x * b->z));
	ret->z = ((a->x * b->y) - (a->y * b->x));
	ret->w = 0;
	return (ret);
}

/* colors addition and subtraction */

t_color *colors_operation(t_color *a, t_color *b, char op)
{
	t_color *ret;
	double (*f) (double a, double b);

	if (op == '+')
		f = add;
	else if (op == '-')
		f = sub;
	else if (op == '/')
		f = mul;
	ret = malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = f(a->r, b->r);
	ret->g = f(a->g, b->g);
	ret->b = f(a->b, b->b);
	return (ret);
}

/* colors multiplication with a scalar */

t_color *color_s_mul(t_color *a, double scalar)
{
	t_color *ret;

	ret = malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = mul(a->r, scalar);
	ret->g = mul(a->g, scalar);
	ret->b = mul(a->b, scalar);
	return (ret);
}

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
/*________________________________________________________________________________*/
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
	ret = malloc (sizeof(t_matrix));
	if (!ret)
		return (NULL);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = get(a, b, i, j);
	}
	return (ret);
}
/*________________________________________________________________________________*/

/* identity matrix multipliyng by any matrix it gives the same matrix */

t_matrix *i_mat(void)
{
	int i;
	int j;
	t_matrix *a;

	i = -1;
	a = malloc(sizeof(t_matrix));
	if (!a)
		return (NULL);
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
		arr[j] = Dot_p(tmp, tpl);
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
	ret = malloc(sizeof(t_matrix));
	if (!ret)
		return (NULL);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[j][i] = a->matrix[i][j];
	}
	return (ret);
}

/* get determinant of 2*2 matrix */

double det_2(t_2_2 *a)
{
	return(sub( mul(a->matrix[0][0], a->matrix[1][1]),\
		 mul(a->matrix[0][1], a->matrix[1][0])));
}



/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */

t_3_3 *sub_m3(t_matrix *a, int row, int col)
{
	t_3_3 *d;
	int i[4];

	d = (t_3_3 *)malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	i[0] = -1;
	i[2] = -1;
	while (++(i[0]) < 4 && ++(i[2]) < 3)
	{
		if (i[0] == row)
			++(i[0]);
		i[1] = -1;
		i[3] = -1;
		while (++(i[1]) < 4 && ++(i[3]) < 3)
		{
			if (i[1] == col)
				++(i[1]);
			d->matrix[i[2]][i[3]] = a->matrix[i[0]][i[1]] ;
		}
	}
	return (d);
}

/* submatrix 2*2 remove a collamn and a row from a 3*3 matrix */

t_2_2 *sub_m2(t_3_3 *a, int row, int col)
{
	t_2_2 *d;
	int i[4];

	d = (t_2_2 *)malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	i[0] = -1;
	i[2] = -1;
	while (++(i[0]) < 3 && ++(i[2]) < 2)
	{
		if (i[0] == row)
			++(i[0]);
		i[1] = -1;
		i[3] = -1;
		while (++(i[1]) < 3 && ++(i[3]) < 2)
		{
			if (i[1] == col)
				++(i[1]);
			d->matrix[i[2]][i[3]] = a->matrix[i[0]][i[1]] ;
		}
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
	return ((det_3(sub_m3(a, row, col))) * cof_sign(row, col));
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
	ret = malloc(sizeof(t_matrix));
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

double radians(double degrees)
{
	return ((degrees / 180) * π);
}

/* translate  point */
t_tuple *transl(t_tuple *point, t_matrix *tr_mtx)
{
	return (tup_mat_mul(tr_mtx, point));
}

/* scall point */
t_tuple *scall(t_tuple *point, t_matrix *scal_mtx)
{
	return (tup_mat_mul(scal_mtx, point));
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

t_ray *ray(t_tuple *origine, t_tuple *direction)
{
	t_ray *ret;

	ret = malloc (sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->o = origine;
	ret->d = direction;
	ret->ud = Normalize(direction);
	return (ret);
}

t_tuple *position(t_ray *ray, double distance)
{
	return (tuples_A_S(ray->o , scalar_multply(ray->d, distance), '+'));
}

t_spher *spher(t_tuple *center, double raduis)
{
	t_spher *ret;

	ret = malloc (sizeof(spher));
	if (!ret)
		return (NULL);
	ret->c = center;
	ret->r = raduis;
	return (ret);
}

double *intersection(t_ray *ray, t_spher *spher)
{
	
	
}

int main()
{
	t_ray *r = ray(cpv(0,0,5,1), cpv(0,0,1,0));
	t_spher *sph = spher(cpv(0,0,0,1), 2);
	
}
