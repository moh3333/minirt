/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2024/12/14 17:12:13 by mthamir          ###   ########.fr       */
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

/* calcul square of a number */
double n_square(double num)
{
	return (num * num);
}

/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a)
{
	return (sqrt((n_square(a->x) + n_square(a->y) + n_square(a->z))));
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
	ret->w = (a->w / v);
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

int equal_matrix(t_matrix *a, t_matrix *b, int base)
{
	int i;
	int j;

	i = 0;
	while (i < base)
	{
		j = 0;
		while (j < base)
		{
			if (!is_equal(a->matrix[i][j], b->matrix[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

double	get_element(t_matrix *a, t_matrix *b, int row, int col)
{
	double result;
	int i;

	result = 0;
	i = 0;
	while (i < 4)
	{
		result += (a->matrix[row][i] * b->matrix[i][col]);
		i++;
	} 
	return (result);
}

t_matrix	*multiply_matrixs(t_matrix *a, t_matrix *b)
{
	int i;
	int j;
	t_matrix *ret;

	i = 0; 
	ret = malloc (sizeof(t_matrix));
	if (!ret)
		return (NULL);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret->matrix[i][j] = get_element(a, b, i, j);
			j++;
		}
		i++;
	}
	return (ret);
}

t_tuple *tuple_matrix_multi(t_matrix *mtx, t_tuple *tpl)
{
	t_tuple *ret;
	t_tuple *tmp;
	double arr[4];
	int j = 0;

	j = 0;
	while (j < 4)
	{
		tmp = creat_p_v(mtx->matrix[j][0], mtx->matrix[j][1],\
		mtx->matrix[j][2], mtx->matrix[j][3]);
		arr[j] = Dot_product(tmp, tpl);
		j++;
	}
	ret = creat_p_v(arr[0], arr[1], arr[2], arr[3]);
	return (ret);
}

// t_tuple *tuple_matrix_multi(t_matrix *mtx, t_tuple *tpl)
// {
// 	t_tuple *ret;
// 	double arr[4];
// 	double result[4];
// 	int i[2];

// 	i[0] = 0;
// 	arr[0] = tpl->x;
// 	arr[1] = tpl->y;
// 	arr[2] = tpl->z;
// 	arr[3] = tpl->w;
// 	ret = malloc (sizeof(t_tuple));
// 	if (!ret)
// 		return (NULL);
// 	while (i[1] < 4)
// 	{
// 		i[0] = 0;
// 		while (i[0] < 4)
// 		{
// 			result[i[1]] += (mtx->matrix[i[1]][i[0]] * arr[i[0]]);
// 			(i[0])++;
// 		}
// 		(i[1])++;
// 	}
// 	ret->x = result[0];
// 	ret->y = result[1];
// 	ret->z = result[2];
// 	ret->w = result[3];
// 	return (ret);
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

// 	void *mlx = mlx_init();
// 	void *window = mlx_new_window(mlx, 2000, 2000, "TEST");
// 	t_projectile *proj = creat_proj(creat_p_v(0, 1, 0, 1), Normalize(creat_p_v(1, 1, 0, 0)));
// 	t_envirement *env = creat_env(creat_p_v(0, -0.1, 0, 0), creat_p_v(-0.01, 0, 0, 0));
// 	int ti = 0;
// 	while (proj->position->y > 0)
// 	{
// 		ti++;
// 		proj = tick(env, proj);
// 	}
// }
/* waiting */