/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/08 17:38:58 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void *ft_malloc(size_t size)
{
	void *ret = malloc(size);
	bzero(ret, size);
	return (ret);
}

double **new_2_2()
{
	double **ret;

	ret = ft_malloc(sizeof(double *) * 2);
	if (!ret)
		return (NULL);
	ret[0] = ft_malloc(sizeof(double ) * 2);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_malloc(sizeof(double ) * 2);
	if (!ret[1])
		return (NULL);
	return (ret);
}

double **new_3_3()
{
	double **ret;

	ret = ft_malloc(sizeof(double *) * 3);
	if (!ret)
		return (NULL);
	ret[0] = ft_malloc(sizeof(double ) * 3);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_malloc(sizeof(double ) * 3);
	if (!ret[1])
		return (NULL);
	ret[2] = ft_malloc(sizeof(double ) * 3);
	if (!ret[2])
		return (NULL);
	return (ret);
}

double **new_4_4()
{
	double **ret;

	ret = ft_malloc(sizeof(double *) * 4);
	if (!ret)
		return (NULL);
	ret[0] = ft_malloc(sizeof(double ) * 4);
	if (!ret[0])
		return (NULL);
	ret[1] = ft_malloc(sizeof(double ) * 4);
	if (!ret[1])
		return (NULL);
	ret[2] = ft_malloc(sizeof(double ) * 4);
	if (!ret[2])
		return (NULL);
	ret[3] = ft_malloc(sizeof(double ) * 4);
	if (!ret[3])
		return (NULL);
	return (ret);
}

/*if p_v is (1) creat point if its 0 creat vector */

t_tuple *cpv(double x, double y, double z, double p_v)
{
	t_tuple *a;

	a = ft_malloc(sizeof(t_tuple));
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
int isequal(double a, double b)
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
double	divi(double a, double b)
{
	return (a / b);
}

/*operation two tuples */
t_tuple *tpl_o(t_tuple *a, t_tuple *b , char op)
{
	t_tuple *ret;
	double	(*f)(double p1, double p2);

	f = NULL;
	ret = NULL;
	if(op == '+')
		f = add;
	else if(op == '-')
		f = sub;
	ret = ft_malloc (sizeof(t_tuple));
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

	opp = ft_malloc (sizeof (t_tuple));
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

	ret = ft_malloc(sizeof (t_tuple));
	if (!ret)
		return (NULL);
	ret->x = (mul(a->x, scalar));
	ret->y = (mul(a->y, scalar));
	ret->z = (mul(a->z, scalar));
	ret->w = a->w;
	return (ret);
}

double	sq(double num)
{
	return(pow(num, 2));
}
/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a)
{
	return (sqrt((sq(a->x) + sq(a->y) + sq(a->z))));
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

	ret = ft_malloc (sizeof (t_tuple));
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
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

/* cross product if "a" and "b" are vector the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple *Cross_p(t_tuple *a, t_tuple *b)
{
	t_tuple *ret;

	ret = ft_malloc(sizeof(t_tuple));
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

	f = NULL;
	if (op == '+')
		f = add;
	else if (op == '-')
		f = sub;
	else if (op == '/')
		f = mul;
	ret = ft_malloc(sizeof(t_color));
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

	ret = ft_malloc(sizeof(t_color));
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
/*________________________________________________________________________________*/

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

/* get determinant of 2*2 matrix */

double det_2(t_2_2 *a)
{
	return(sub( mul(a->matrix[0][0], a->matrix[1][1]),\
		 mul(a->matrix[0][1], a->matrix[1][0])));
}

void get_sub(double *a, double **d, int col)
{
	int p = 0;
	int s = 0;

	while (p < 4)
	{
		if (p == col && col < 3)
			p++;
		if (p == col && col == 3)
			break;
		(*d)[s] = a[p];
		s++;
		p++;
	}
}

/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */

t_3_3 *sub_m3(t_matrix *a, int row, int col)
{
	t_3_3 *d;
	int i, j;

	d = (t_3_3 *)ft_malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	d->matrix = new_3_3();
	i = 0;
	j = 0;
	while (i < 4)
	{
		if (i == row && row < 3)
			i++;
		if (i == row && row == 3)
			break;
		get_sub(a->matrix[i], &d->matrix[j], col);
		i++;
		j++;
	}
	return (d);
}

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

	ret = ft_malloc (sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->o = origine;
	ret->d = direction;
	ret->ud = Normalize(direction);
	return (ret);
}

t_tuple *position(t_ray *ray, double distance)
{
	return (tpl_o(ray->o , scalar(ray->d, distance), '+'));
}

t_spher *spher(t_tuple *center, double raduis, int id)
{
	t_spher *ret;

	ret = ft_malloc (sizeof(t_spher));
	if (!ret)
		return (NULL);
	ret->c = center;
	ret->r = raduis;
	ret->id = id;
	ret->transform = i_mat();
	ret->material = material();
	return (ret);
}

static double *eq_inter(t_ray *ray1 , t_spher *spher)
{
	double		*arr;

	arr = ft_malloc (4 * sizeof (double));
	if (!arr)
		return (NULL);
	arr[0] = Dot_p(ray1->d, ray1->d);
	arr[1] = 2.0 * (Dot_p(ray1->o, ray1->d));
	arr[2] = (Dot_p(ray1->o, ray1->o) - sq(spher->r));
	arr[3] = sq(arr[1]) - (4 * (arr[0] * arr[2]));
	return (arr);
}
double *new_t()
{
	double *ret = ft_malloc(sizeof(double ) * 2);
	if(!ret)
		return (NULL);
	return (ret);
}

t_intersect	*intersect(t_ray *ray, t_spher *sph)
{
	t_intersect *inter;
	t_ray *ray1;
	double *arr;

	ray1 = transform(ray, inverse(sph->transform));
	arr = eq_inter(ray1, sph);
	if (!arr)
		return (NULL);
	inter = ft_malloc(sizeof(t_intersect));
	if (!inter)
		return (NULL);
	inter->t = new_t();
	inter->t[0] = (-arr[1] - sqrt(arr[3])) / (2 * (arr[0]));
	inter->t[1] = (-arr[1] + sqrt(arr[3])) / (2 * (arr[0]));
	inter->object = sph;
	inter->ray = ray1;
	if (arr[3] < 0)
		return (NULL);
	return (inter);
}

double hit(double *arr)
{
	if (arr[0] < 0 && arr[1] < 0)
		return (0);
	return (1);
}

double *intersections(int num, ...)
{
	va_list a;
	double *arr;
	int i;

	i = -1;
	arr = ft_malloc (num * sizeof(double));
	if (!arr)
		return (NULL);
	va_start(a, num);
	while (++i < num)
		arr[i] = va_arg(a, double);
	return (arr);
}
double ft_max(double *arr, int num)
{
	int i;
	double max;

	i = -1;
	max = -1;
	while (++i < num)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return (max);
}

double hit_p(double *arr, int num)
{
	int i;
	double min;

	i = -1;
	min = ft_max(arr, num);
	if (min < 0)
		return (-2147483648);
	if (min == 0)
		return (min);
	while (++i < num)
	{
		if (arr[i] < min)
			min = arr[i];
	}
	return (min);
}

t_ray *transform(t_ray *t, t_matrix *mat)
{
	t_ray *ra;

	ra = ft_malloc(sizeof(t_ray));
	if (!ra)
		return (NULL);
	ra->o = tup_mat_mul(mat, t->o);
	ra->d = tup_mat_mul(mat , t->d);
	ra->ud = Normalize(ra->d);
	return (ra);
}
void	set_tranform(t_spher *sph, t_matrix *mat)
{
	*sph->transform = *mat;
}

t_tuple *normal_at(t_spher *sph, t_tuple *point)
{
	t_tuple *object_p;
	t_tuple *object_normal;
	t_tuple *world_normal;

	object_p = tup_mat_mul(inverse(sph->transform), point);
	object_normal = tpl_o(object_p, cpv(0,0,0,1), '-');
	world_normal = tup_mat_mul(transpose(inverse(sph->transform)), object_normal);
	world_normal->w = 0;
	return (Normalize(world_normal));
}

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
	return (tpl_o(in, (scalar(normal, mul(Dot_p(in, normal), 2))), '-'));
}

t_light *light_source(t_tuple *position, t_color *color, double brightness)
{
	t_light *light;

	light = ft_malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->brightness = brightness;
	light->color = color;
	return (light);
}

t_material *material()
{
	t_material *mate = ft_malloc(sizeof(t_material));

	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	return (mate);
}
double get_color(t_color *color)
{
	double color_in_double;
	double r_norm = color->r / 255.0;
	double g_norm = color->g / 255.0;
	double b_norm = color->b / 255.0;

	color_in_double = (r_norm * sq(256.0)) + (g_norm * 256.0) + b_norm;
	return (color_in_double);
}

// double lighting(t_lighting *lighting)
// {
// 	t_color *effective_color;
// 	t_color *ambiant;
// 	t_tuple *light_vec;
// 	t_tuple *reflect_vec;
// 	double reflect_dot_camera;
// 	double factor;
// 	double light_dot_normal;

// 	effective_color = color_s_mul(lighting->material->color, lighting->light->brightness);
// 	light_vec = Normalize(tpl_o(lighting->light->position, lighting->point, '-'));
// 	ambiant = color_s_mul(effective_color, lighting->material->ambiant);
// 	light_dot_normal = Dot_p(light_vec, lighting->normal_vec);
// 	if (light_dot_normal < 0)
// 	{
// 		lighting->material->diffuse = BLACK;
// 		lighting->material->specular = BLACK;
// 	}
// 	else
// 	{
// 		lighting->material->diffuse = get_color(color_s_mul(effective_color, mul(lighting->material->diffuse, light_dot_normal)));
// 		reflect_vec = reflect(opp(light_vec), lighting->normal_vec);
// 		reflect_dot_camera = Dot_p(reflect_vec, lighting->camera->cam_ray->d);
// 		if (reflect_dot_camera <= 0)
// 			lighting->material->specular = BLACK;
// 		else
// 		{
// 			factor = pow(reflect_dot_camera, lighting->material->shininess);
// 			lighting->material->specular = mul(lighting->light->brightness, lighting->material->specular * factor);

// 		}
// 	}
// 	return (lighting->material->ambiant + lighting->material->diffuse + lighting->material->specular);
// }
double li(t_material *m, t_light *light, t_tuple *point, t_tuple *eyev, t_tuple *normalv)
{
	double effective_color = get_color(m->color) * light->brightness;
	t_tuple *lightv = Normalize(tpl_o(light->position, point, '-'));
	double ambiant = effective_color * m->ambiant;
	double light_dot_normal = Dot_p(lightv, normalv);
	double diffuse = 0;
	double specular = 0;
	double factor = 0;
	if (light_dot_normal < 0){
		diffuse = 0;
		specular = 0;
	}
	else{
		diffuse = effective_color * m->diffuse * light_dot_normal;
	}
	t_tuple *reflectv = reflect(opp(lightv), normalv);
	double reflect_dot_eye = Dot_p(reflectv, eyev);
	if(reflect_dot_eye <= 0)
		specular = 0;
	else{
		factor = pow(reflect_dot_eye, m->shininess);
		specular = light->brightness * m->specular * factor;
	}
	return (ambiant+diffuse+specular);
}

double get_closest(double *t)
{
	if (t[0] < 0 && t[1] > 0)
		return (t[1]);
	else if (t[1] < 0 && t[0] > 0)
		return (t[0]);
	else if (t[0] > 0 && t[1] > 0)
	{
		if (t[0] < t[1])
			return (t[0]);
		else if (t[0] > t[1])
			return (t[1]);
		else if (t[0] == t[1])
			return (t[1]);
	}
	return (0);
}

// int main()
// {
// 	// t_material *m = material();
// 	// m->color = malloc(sizeof(t_color));
// 	// m->color->r = 255;
// 	// m->color->g = 0;
// 	// m->color->b = 0;
// 	// t_color *color = ft_malloc(sizeof(t_color));
// 	// color->r = 1;
// 	// color->g = 1;
// 	// color->b = 1;
// 	// t_light *light = light_source(cpv(0,10,-10,1), color, 1);
// 	// double result = li(m, light, cpv(0,0,0,1) , cpv(0,0,-1,0),cpv(0, -(sqrt(2)/2), -(sqrt(2)/2), 0));
// 	// t_color *f = malloc(sizeof(t_color));
// 	// f->r = 1.6364;
// 	// f->g = 1.6364;
// 	// f->b = 1.6364;
// 	// double dd = get_color(f);
// 	// printf("double %.5f\n", result);
// 	// printf("double %.5f\n", dd);
// }

// int main()
// {
// 	t_tuple *s = reflect(cpv(0,-1,0,0), cpv(sqrt(2)/2.0,(sqrt(2)/2.0), 0,0));
// 	printf("%.5f\n%.5f\n%.5f\n", s->x, s->y, s->z);
// }
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
int main()
{
	double wall_size = 600.0;
	double canvas_pixel = 600.0;
	double pixel_size = wall_size / canvas_pixel;
	double half = wall_size / 2.0;
	double  color = 0xFFFFFF;
	t_spher *sph = spher(cpv(0,0,0,1), 1, 0);  //unit spher
	sph->transform = scal_mat(30, 30, 1);
	void *mlx = mlx_init(600, 600, "test", 1);
	t_tuple *origine = cpv(0,0,-10,1);
	mlx_image_t *image = mlx_new_image(mlx, 600, 600);
	mlx_image_to_window(mlx, image, 0, 0);
	for(double y = 0; y < canvas_pixel; y++){
		double world_y = half - (pixel_size * y);
		for(double x = 0; x < canvas_pixel; x++){
			double world_x = -half + (pixel_size * x);
			t_tuple *pixel_position = cpv(world_x, world_y, 20, 1);
			t_ray *r = ray(origine, Normalize(tpl_o(pixel_position, origine, '-')));
			t_intersect *i = intersect(r, sph);
			if (i &&  hit(i->t))
				mlx_put_pixel(image, x, y, color);
			else
				mlx_put_pixel(image, x, y, BLACK);

		}
	}
	mlx_loop(mlx);
}
