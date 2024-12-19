/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2024/12/19 18:53:27 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*if p_v is (1) creat point if its 0 creat vector */

t_tuple *creat_p_v(double x, double y, double z, int p_v)
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
int is_p_v(t_tuple *a)
{
	return ((a->w == 1));
}

/* compare two floating point number we use a constant  */
int is_equal(double a, double b)
{
	return ((fabs(a-b) < EPSILON));
}
/* add two floating point number */
double	add(double a, double b)
{
	return (a + b);
}

/* subtract two floating point number */
double	subtruct(double a, double b)
{
	return (a - b);
}

/* multiply two floating point number */
double	multiply(double a, double b)
{
	return (a * b);
}

/* divide two floating point number */
double	divide(double a, double b)
{
	return (a / b);
}

/*operation two tuples */
t_tuple *tuples_A_S(t_tuple *a, t_tuple *b , char op)
{
	t_tuple *ret;
	double	(*f)(double p1, double p2);

	if(op == '+')
		f = add;
	else if(op == '-')
		f = subtruct;
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
t_tuple *t_opposite(t_tuple *a)
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
t_tuple *scalar_multply(t_tuple *a, double scalar)
{
	t_tuple *ret;

	ret = malloc(sizeof (t_tuple));
	if (!ret)
		return (NULL);
	ret->x = (multiply(a->x, scalar));
	ret->y = (multiply(a->y, scalar));
	ret->z = (multiply(a->z, scalar));
	ret->w = (multiply(a->w, scalar));
	return (ret);
}

/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a)
{
	return (sqrt((pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2))));
}

/* check if its a unit vector */
double	is_unit_v(t_tuple *a)
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
we need it to compare the direction of the two vectors */
/* if the two vectors are unit theire dot product is actually the cosine of the ongle between them */
double	Dot_product(t_tuple *a, t_tuple *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w));
}

/* cross product if "a" and "b" are vector the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple *Cross_vector(t_tuple *a, t_tuple *b)
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
		f = subtruct;
	else if (op == '/')
		f = multiply;
	ret = malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = f(a->r, b->r);
	ret->g = f(a->g, b->g);
	ret->b = f(a->b, b->b);
	return (ret);
}

/* colors multiplication with a scalar */

t_color *colors_scalar_multiply(t_color *a, double scalar)
{
	t_color *ret;

	ret = malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = multiply(a->r, scalar);
	ret->g = multiply(a->g, scalar);
	ret->b = multiply(a->b, scalar);
	return (ret);
}

/* checks if two matrix are equals*/

int equal_matrix(t_matrix *a, t_matrix *b)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (!is_equal(a->matrix[i][j], b->matrix[i][j]))
				return (0);
		}
	}
	return (1);
}

/*helper function that help multiplying two matrixs */

double	get_element(t_matrix *a, t_matrix *b, int row, int col)
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

t_matrix	*multiply_matrixs(t_matrix *a, t_matrix *b)
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
			ret->matrix[i][j] = get_element(a, b, i, j);
	}
	return (ret);
}

/* identity matrix multipliyng by any matrix it gives the same matrix */

t_matrix *identity_matrix(void)
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

t_tuple *tuple_matrix_multi(t_matrix *mtx, t_tuple *tpl)
{
	t_tuple *ret;
	t_tuple *tmp;
	double arr[4];
	int j;

	j = -1;
	while (++j < 4)
	{
		tmp = creat_p_v(mtx->matrix[j][0], mtx->matrix[j][1],\
		mtx->matrix[j][2], mtx->matrix[j][3]);
		arr[j] = Dot_product(tmp, tpl);
	}
	ret = creat_p_v(arr[0], arr[1], arr[2], arr[3]);
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

double determinant_2(t_2_2 *a)
{
	return(subtruct( multiply(a->matrix[0][0], a->matrix[1][1]),\
		 multiply(a->matrix[0][1], a->matrix[1][0])));
}



/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */

t_3_3 *submatrix_3(t_matrix *a, int row, int col)
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

t_2_2 *submatrix_2(t_3_3 *a, int row, int col)
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
	return (determinant_2(submatrix_2(a, row, col)));
}

/* get the cofactor sign depending on the case the row and col removed share in the matrix */

double cofactor_sign(int r, int c)
{
	if ((!(r % 2) && (c % 2)) || ((r % 2) && (!(c % 2))))
		return (-1);
	return (1);
}

/* gettin the cofactor of the 3*3 matrix */

double cofactor_3(t_3_3 *a, int row , int col )
{
	return ((ft_minor(a, row , col) * cofactor_sign(row, col)));
}

/*getting the determinant of the 3*3 matrix u have the choice to work with the cols o rows
u will get the same  result  */
double determinant_3(t_3_3 *a)
{
	return ((cofactor_3(a, 0, 0) * a->matrix[0][0]) + \
		(cofactor_3(a, 0, 1) * a->matrix[0][1]) + \
		(cofactor_3(a, 0, 2) * a->matrix[0][2]));
}

double	cofactor(t_matrix *a, int row , int col)
{
	return ((determinant_3(submatrix_3(a, row, col))) * cofactor_sign(row, col));
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

t_matrix *transl_matrix(double x, double y, double z)
{
	t_matrix *ret;

	ret = identity_matrix();
	ret->matrix[0][3] = x;
	ret->matrix[1][3] = y;
	ret->matrix[2][3] = z;
	return (ret);
}

/* get the scalling matrix */
t_matrix *scal_matrix(double x, double y, double z)
{
	t_matrix *ret;

	ret = identity_matrix();
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
t_tuple *translation(t_tuple *point, t_matrix *tr_mtx)
{
	return (tuple_matrix_multi(tr_mtx, point));
}

/* scall point */
t_tuple *scalling(t_tuple *point, t_matrix *scal_mtx)
{
	return (tuple_matrix_multi(scal_mtx, point));
}

/* rotat a vector or a point to an axis x y or z */
t_matrix *rotat_matrix(double radians, char axis)
{
	t_matrix *ret;
	int r[2];

	r[0] = 0;
	r[1] = 0;
	ret = identity_matrix();
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

t_matrix *skewing_matrix(double *arr)
{
	t_matrix *ret;

	ret = identity_matrix();
	ret->matrix[0][1] = arr[0];
	ret->matrix[0][2] = arr[1];
	ret->matrix[1][0] = arr[2];
	ret->matrix[1][2] = arr[3];
	ret->matrix[2][0] = arr[4];
	ret->matrix[2][1] = arr[5];
	return (ret);
}

int main()
{
	t_matrix *s = rotat_matrix(radians(90), 'x');
	t_matrix *b = scal_matrix(5,5,5);
	t_matrix *c = transl_matrix(10,5,7);
	t_tuple *a = tuple_matrix_multi(multiply_matrixs(c, multiply_matrixs(b, s)), creat_p_v(1,0,1,1));
	printf("x == %.5f\n", a->x);
	printf("y == %.5f\n", a->y);
	printf("z == %.5f\n", a->z);
	printf("w == %.5f\n", a->w);
	
}
/* testing the skeewing (shearing ) transformation */
// int main()
// {
// 	double arr[6] = {0,0,0,0,0,1};
// 	t_tuple *a = tuple_matrix_multi(skewing_matrix(arr), creat_p_v(2,3,4,1));
// 	printf("x == %.5f\n", a->x);
// 	printf("y == %.5f\n", a->y);
// 	printf("z == %.5f\n", a->z);
// 	printf("w == %.5f\n", a->w);

// }

/* testing rotat a vector or point around an axis x y or z */
// int main()
// {
// 	t_tuple *a = tuple_matrix_multi((rotat_matrix(radians(45), 'z')), creat_p_v(0,1,0,1));
// 	printf("x == %.5f\n", a->x);
// 	printf("y == %.5f  ====  %.5f\n", a->y , (sqrt(2) / 2));
// 	printf("z == %.5f\n", a->z);
// 	printf("w == %.5f\n", a->w);
// }

/* testing scalling a vector or point it affect to both of them by a scallar matrix */
// int main()
// {
	// t_tuple *r = scalling(creat_p_v(2,3,4,1), scal_matrix(-1,1,1));
	// printf("%.0f\n%.0f\n%.0f\n%.0f\n", r->x, r->y, r->z, r->w);
	/* scalling by inverse */
	// t_tuple *r = scalling(creat_p_v(-4,6,8,1), inverse(scal_matrix(2,3,4)));
	// printf("%.0f\n%.0f\n%.0f\n%.0f\n", r->x, r->y, r->z, r->w);
// }

/*test translate a point or vector but it does not affect with vectors && by transalte matrix and its inverse  */
// int main()
// {
// 	t_tuple *r = translat_point(creat_p_v(-3,4,5,1), inverse(transl_matrix(5,-3,2)));
// 	printf("%.0f\n%.0f\n%.0f\n%.0f\n", r->x, r->y, r->z, r->w);
// }
/* testing the inverse of matrixs */

// int main()
// {
// 	t_matrix a;
// 	t_matrix b;

// 	a.matrix[0][0] = 3;
// 	a.matrix[0][1] = -9;
// 	a.matrix[0][2] = 7;
// 	a.matrix[0][3] = 3;

// 	a.matrix[1][0] = 3;
// 	a.matrix[1][1] = -8;
// 	a.matrix[1][2] = 2;
// 	a.matrix[1][3] = -9;

// 	a.matrix[2][0] = -4;
// 	a.matrix[2][1] = 4;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;

// 	a.matrix[3][0] = -6;
// 	a.matrix[3][1] = 5;
// 	a.matrix[3][2] = -1;
// 	a.matrix[3][3] = 1;
// /*__________________________________*/

// 	b.matrix[0][0] = 8;
// 	b.matrix[0][1] = 2;
// 	b.matrix[0][2] = 2;
// 	b.matrix[0][3] = 2;

// 	b.matrix[1][0] = 3;
// 	b.matrix[1][1] = -1;
// 	b.matrix[1][2] = 7;
// 	b.matrix[1][3] = 0;

// 	b.matrix[2][0] = 7;
// 	b.matrix[2][1] = 0;
// 	b.matrix[2][2] = 5;
// 	b.matrix[2][3] = 4;

// 	b.matrix[3][0] = 6;
// 	b.matrix[3][1] = -2;
// 	b.matrix[3][2] = 0;
// 	b.matrix[3][3] = 5;
	// t_matrix *d = multiply_matrixs(&b, &a);
	// int i = 0;
	// int j = 0;
	// while (i < 4)
	// {
	// 	j = 0;
	// 	while (j < 4)
	// 	{
	// 		printf("%.5f  |", d->matrix[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// printf("\n");
	// t_matrix *ret = multiply_matrixs( d, inverse(&a));
	// i = 0;
	// j = 0;
	// while (i < 4)
	// {
	// 	j = 0;
	// 	while (j < 4)
	// 	{
	// 		printf("%.5f  |", ret->matrix[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// if (equal_matrix(&a, multiply_matrixs(multiply_matrixs(&a, &b), inverse(&b))))
	// 	printf("vereything works as expected \n");
	// else
	// 	printf("rak ghir katkhawer\n");
	

// }

/*waiting */

/*testing the determinant of the 3*3 matrix */
// int main()
// {
// 	t_3_3 a;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 6;

// 	a.matrix[1][0] = -5;
// 	a.matrix[1][1] = 8;
// 	a.matrix[1][2] = -4;

// 	a.matrix[2][0] = 2;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;

// 	double r = cofactor_3(&a, 0, 0);
// 	double r1 = cofactor_3(&a, 1, 0);
// 	double r2 = cofactor_3(&a, 2, 0);
// 	// double r3 = determinant_2(submatrix_2(&a));
// 	printf("%.0f\n", r);
// 	printf("%.0f\n", r1);
// 	printf("%.0f\n", r2);
// 	printf("%.0f\n", determinant_3(&a));
// 	printf("%.0f\n", (((r*a.matrix[0][0])+(r1*a.matrix[1][0])+(r2*a.matrix[2][0]))));
// }

/* testing the minor of the 3*3 matrix */
// int main()
// {
// 	t_3_3 a;

// 	a.matrix[0][0] = 3;
// 	a.matrix[0][1] = 5;
// 	a.matrix[0][2] = 0;

// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = -1;
// 	a.matrix[1][2] = -7;

// 	a.matrix[2][0] = 6;
// 	a.matrix[2][1] = -1;
// 	a.matrix[2][2] = 5;

// 	double r = ft_minor(&a, 1, 0);
// 	printf("%.0f\n", r);
// }

/* testing submatrix 2 and 3 */

// int main()
// {
// 	t_matrix a;

// 	a.matrix[0][0] = -6;
// 	a.matrix[0][1] = 1;
// 	a.matrix[0][2] = 1;
// 	a.matrix[0][3] = 6;

// 	a.matrix[1][0] = -8;
// 	a.matrix[1][1] = 5;
// 	a.matrix[1][2] = 8;
// 	a.matrix[1][3] = 6;

// 	a.matrix[2][0] = -1;
// 	a.matrix[2][1] = 0;
// 	a.matrix[2][2] = 8;
// 	a.matrix[2][3] = 2;

// 	a.matrix[3][0] = -7;
// 	a.matrix[3][1] = -1;
// 	a.matrix[3][2] = -1;
// 	a.matrix[3][3] = 1;

// 	t_3_3 *h = submatrix_3(&a, 2, 1);

// 	int i, j;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			printf("  %.0f |", h->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	} 
// 	printf("\n");
// 	t_2_2 *d = submatrix_2(h, 0, 2);
// 	i = 0;
// 	while (i < 2)
// 	{
// 		j = 0;
// 		while (j < 2)
// 		{
// 			printf("  %.0f |", d->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	} 
// }



/* determinant of 2*2 matrix test */
// int main()
// {
// 	t_2_2 *a;
// 	a = malloc(sizeof(t_2_2));
// 	a->matrix[0][0] = 1;
// 	a->matrix[0][1] = 5;
// 	a->matrix[1][0] = -3;
// 	a->matrix[1][1] = 2;
// 	printf("%.0f\n", determinant_2(a));
// }

/* transpose test */

// int main()
// {
// 	t_matrix a;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;

// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = 4;
// 	a.matrix[1][2] = 4;
// 	a.matrix[1][3] = 2;

// 	a.matrix[2][0] = 8;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;

// 	a.matrix[3][0] = 0;
// 	a.matrix[3][1] = 0;
// 	a.matrix[3][2] = 0;
// 	a.matrix[3][3] = 1;

// 	int i = 0;
// 	int j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", a.matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	printf("_____________\n");
// 	t_matrix *ret = transpose(&a);
// 	i = 0;
// 	j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", ret->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

/*multiply a identity matrice by a tuple and by a matrix test */

// int main()
// {
// 	t_matrix a;
// 	t_tuple b;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;

// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = 4;
// 	a.matrix[1][2] = 4;
// 	a.matrix[1][3] = 2;

// 	a.matrix[2][0] = 8;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;

// 	a.matrix[3][0] = 0;
// 	a.matrix[3][1] = 0;
// 	a.matrix[3][2] = 0;
// 	a.matrix[3][3] = 1;

// 	b.x = 1;
// 	b.y = 2;
// 	b.z = 3;
// 	b.w = 1;
// 	t_matrix *iden = identity_matrix();
// 	iden->matrix[0][1] = 6;
// 	t_tuple *re = tuple_matrix_multi(iden, &b);
// 	int i = 0;
// 	int j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", iden->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	printf("%.0f\n%.0f\n%.0f\n%.0f\n", re->x, re->y, re->z, re->w);
// 	printf("__________________________________________\n");
// 	t_matrix *ret = multiply_matrixs(&a, identity_matrix());

// 	i = 0;
// 	j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", ret->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

/*multiply a matrice by a tuple test */

// int main()
// {
// 	t_matrix a;
// 	t_tuple b;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;
// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = 4;
// 	a.matrix[1][2] = 4;
// 	a.matrix[1][3] = 2;
// 	a.matrix[2][0] = 8;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;
// 	a.matrix[3][0] = 0;
// 	a.matrix[3][1] = 0;
// 	a.matrix[3][2] = 0;
// 	a.matrix[3][3] = 1;

// 	b.x = 1;
// 	b.y = 2;
// 	b.z = 3;
// 	b.w = 1;

// 	t_tuple *ret = tuple_matrix_multi(&a, &b);
// 	printf("%.0f\n%.0f\n%.0f\n%.0f\n", ret->x, ret->y, ret->z, ret->w);

// }
/*  test for multiplying matrices */

// int main()
// {
// 	t_matrix a;
// 	t_matrix b;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;
// 	a.matrix[1][0] = 5;
// 	a.matrix[1][1] = 6;
// 	a.matrix[1][2] = 7;
// 	a.matrix[1][3] = 8;
// 	a.matrix[2][0] = 9;
// 	a.matrix[2][1] = 8;
// 	a.matrix[2][2] = 7;
// 	a.matrix[2][3] = 6;
// 	a.matrix[3][0] = 5;
// 	a.matrix[3][1] = 4;
// 	a.matrix[3][2] = 3;
// 	a.matrix[3][3] = 2;

// 	b.matrix[0][0] = -2;
// 	b.matrix[0][1] = 1;
// 	b.matrix[0][2] = 2;
// 	b.matrix[0][3] = 3;
// 	b.matrix[1][0] = 3;
// 	b.matrix[1][1] = 2;
// 	b.matrix[1][2] = 1;
// 	b.matrix[1][3] = -1;
// 	b.matrix[2][0] = 4;
// 	b.matrix[2][1] = 3;
// 	b.matrix[2][2] = 6;
// 	b.matrix[2][3] = 5;
// 	b.matrix[3][0] = 1;
// 	b.matrix[3][1] = 2;
// 	b.matrix[3][2] = 7;
// 	b.matrix[3][3] = 8;

// 	t_matrix *ret = multiply_matrixs(&a, &b);

// 	int i = 0;
// 	int j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", ret->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}

// }

/*__________________________  putting theme together   ______________________________*/
/*______________________________________________*/

/*just for testing */


// typedef struct s_projectile	{
// 	t_tuple *position ;
// 	t_tuple *velocity ;
// } 		t_projectile;

// typedef struct s_envirement	{
// 	t_tuple *gravity;
// 	t_tuple *wind;
// }	t_envirement;

// t_projectile *creat_proj(t_tuple *position, t_tuple *velocity)
// {
// 	t_projectile *proj = malloc (sizeof(t_projectile));
// 	if (!proj)
// 		return (NULL);
// 	proj->position = position;
// 	proj->velocity = velocity;
// 	return (proj);
// }

// t_envirement *creat_env(t_tuple *position , t_tuple *wind)
// {
// 	t_envirement *env = malloc (sizeof(t_envirement));
// 	if (!env)
// 		return (NULL);
// 	env->gravity = position;
// 	env->wind = wind;
// 	return (env);
// }

// t_projectile *tick(t_envirement *env, t_projectile *proj)
// {
// 	t_tuple *pr ;
// 	t_tuple *pd ;
// 	pr = tuples_A_S(proj->position, proj->velocity, '+');
// 	pd = tuples_A_S(proj->velocity, tuples_A_S(env->gravity, env->wind, '+'), '+');
// 	return (creat_proj(pr, pd));
// }

// int main()
// {
// 	t_projectile *proj = creat_proj(creat_p_v(0, 1, 0, 1), Normalize(creat_p_v(1, 1, 0, 0)));
// 	t_envirement *env = creat_env(creat_p_v(0, -0.1, 0, 0), creat_p_v(-0.01, 0, 0, 0));
// 	int ti = 0;
// 	while (1)
// 	{
// 		ti++;
// 		printf("proj y == %.5f\n", proj->position->y);
// 		printf("proj x == %.5f\n", proj->position->x);
// 		printf("proj z == %.5f\n", proj->position->z);
// 		printf("volecity y == %.5f\n", proj->velocity->y);
// 		printf("volecity x == %.5f\n", proj->velocity->x);
// 		printf("volecity z == %.5f\n", proj->velocity->z);
// 		proj = tick(env, proj);
// 		printf("\n");
// 		sleep(1);
// 	}
// 	printf("the projectile touch the ground");
// }
/* waiting */