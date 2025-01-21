/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:22 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 18:25:03 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <libc.h>
#include <math.h>
#include <stdarg.h>
#include <MLX42.h>


#define	EPSILON 0.00001
#define SPHER 1
#define SPH 1
#define BLACK 0x0000000FF

typedef struct s_color	{
	double r;
	double g;
	double b;
}	t_color;

typedef struct s_material
{
	t_color *color;
	double ambiant;
	double diffuse;
	double specular;
	double shininess;
}	t_material;


typedef struct s_tuple	{
	double x;
	double y;
	double z;
	double w;
} 	t_tuple;

typedef struct s_light
{
	t_tuple *position;
	t_color *color;
	double brightness;
}	t_light;

typedef struct s_matrix{
	double **matrix;
}	t_matrix;

typedef struct s_2_2{
	double **matrix;
}	t_2_2;

typedef struct s_3_3{
	double **matrix;
}	t_3_3;

typedef struct s_ray
{
	t_tuple *o;
	t_tuple *d;
	t_tuple *ud;
}	t_ray;

typedef struct s_spher
{
	double	r;
	int		id;
	t_matrix *transform;
	t_tuple	*c;
	t_color *color;
	t_material *material;
	t_matrix *inverse_m;
	t_matrix *transpose_inverse;

}	t_spher;

typedef struct s_object
{
	int type;
	t_spher *shape;
} t_object;

typedef struct s_intersect t_intersect;
typedef struct s_intersect
{
	t_ray *ray;
	t_object *object;
	double *t;
	t_intersect *next;
}  t_intersect;

typedef struct s_camera
{
	t_ray *cam_ray;
	void *mlx;
	double pixel_size;
	double half_width;
	double half_hight;
	double field_of_view;
	double aspect_ratio;
	double horizontal_size;
	double vertical_size;
	t_matrix *transform;
	t_matrix *transform_inverse;
}			t_camera;

typedef struct s_lighting
{
	t_material *material;
	t_tuple *point;
	t_light *light;
	t_camera *camera;
	t_tuple *normal_vec;
}	t_lighting;
t_material *material();


typedef struct s_world
{
	int object_count;
	t_light light[100];
	t_object object[200];
}	t_world;

typedef struct s_comps
{
	double t;
	t_object *object;
	t_tuple *point;
	t_tuple *eyev;
	t_tuple *normalv;
	bool inside;
}	t_comps;

/* creat a point or a vector */
t_tuple	*cpv(double x, double y, double z, double p_v);
/* checks if its a point or a vector if true(1) its point else its vector */
int ispoint(t_tuple *a);
/* checks if two floating point number are equal or not if true(1) are equal else not*/
int isequal(double a, double b);
/* add two floating point number */
double	add(double a, double b);
/* subtract two floating point number */
double	sub(double a, double b);
/* multiply two floating point number */
double	mul(double a, double b);
/* divide two floating point number */
double	divi(double a, double b);
/* operation between two tuples addition and subtraction */
t_tuple *tpl_o(t_tuple *a, t_tuple *b , char op);
/*get the opposite vector of a given one */
t_tuple *opp(t_tuple *a);
/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple *a, double scalar);
/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a);
/* check if its a unit vector */
double	isunit(t_tuple *a);
/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
t_tuple *Normalize(t_tuple *a);
/* we use it to compare between two vector direction and knowing the angle between them */
double	Dot_p(t_tuple *a, t_tuple *b);
/* the result is a vector that its perpodicular to both of the two used vectors*/
t_tuple *Cross_p(t_tuple *a, t_tuple *b);
/* get squar of a number */
double	sq(double num);
/* colors addition and subtraction and multiplication */
t_color *colors_operation(t_color *a, t_color *b, char op);
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/* checks if two matrix are equals*/
int equal_mat(t_matrix *a, t_matrix *b);
/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b);
/* identity matrix multipliyng by any matrix it gives the same matrix */
t_matrix *i_mat(void);
/* multipling a matrix by  tuple creat another tuple */
t_tuple *tup_mat_mul(t_matrix *mtx, t_tuple *tpl);
/*transpose take a matrix and change its rows to collomns and its collomns to rows */
t_matrix *transpose(t_matrix *a);
/* get determinant of 2*2 matrix */
double det_2(t_2_2 *a);
/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */
t_3_3 *sub_m3(t_matrix *a, int row, int col);
/* submatrix 2*2 remove a collamn and a row from a 3*3 matrix */
t_2_2 *sub_m2(t_3_3 *a, int row, int col);
/* is the determinant of a 3*3 submatrix after removing a row and col */
double	ft_minor(t_3_3 *a, int row, int col);
/* get the cofactor sign depending on the case the row and col removed share in the matrix */
double cof_sign(int r, int c);
/* gettin the cofactor of the 3*3 matrix */
double cof_3(t_3_3 *a, int row , int col );
/*getting the determinant of the 3*3 matrix u have the choice to work with the cols o rows
u will get the same  result  */
double det_3(t_3_3 *a);
/* get cofactor of a matrix 4*4 */
double	cofactor(t_matrix *a, int row , int col);
/* get detirminant of a 4*4 matrix */
double determinant(t_matrix *a);
/*checks the matrix inverbility is it return 0 mean thats not invertible */
double invertible(t_matrix *a);
/* get the inverse of a matrix */
t_matrix *inverse(t_matrix *a);
/* get the translation matrix we need to translate a point */
t_matrix *transl_mat(double x, double y, double z);
/* get the scalling matrix */
t_matrix *scal_mat(double x, double y, double z);
/* change from degrees to radians */
double radians(double degrees);
/* translation of a point  */
t_tuple *transl(t_tuple *point, t_matrix *tr_mtx);
/* scall point */
t_tuple *scall(t_tuple *point, t_matrix *scal_mtx);
/* rotat a vector or a point to an axis x y or z */
t_matrix *rotat_matrix(double radians, char axis);
/* get teh skewiing (shearing ) matrix */
t_matrix *skew_mat(double *arr);
/* creat a ray wih an origine and a direction */
t_ray *ray(t_tuple *origine, t_tuple *direction);
/* shows how far the ray travels in (x distance) seconds  (Computing a point from a distance)*/
t_tuple *position(t_ray *ray, double distance);
/* creat a sphere with given enter and raduis */
t_spher *spher(t_tuple *center, double raduis, int id, t_matrix *tr);
/* check rays sphere intersection and fill the t_intersect struct with object type and object and intersection points */
t_intersect	*intersect(t_ray *ray, t_spher *spher);
t_ray *transform(t_ray *t, t_matrix *mat);
/* get the normal vector on a point on the spher*/
t_tuple *normal_at(t_spher *sph, t_tuple *point);
/* set the transformation matrix on sphere struct */
void	set_tranform(t_spher *sph, t_matrix *mat);
/* colors addition and subtraction */
t_color *colors_operation(t_color *a, t_color *b, char op);
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/* get diffuse and ambiant color ona apoint */
t_color *compute_lightning(t_material *m, t_light *light, t_tuple *pos,t_tuple *eyev, t_tuple *normalv);
void *ft_malloc(size_t size);
double **new_2_2();
double **new_3_3();
double **new_4_4();
double *new_t(int count);
double hit(double *arr);
double *intersections(int num, ...);
double ft_max(double *arr, int num);
double hit_p(double *arr, int num);
t_light *light_source(t_tuple *position, t_color *color, double brightness);
t_tuple *reflect(t_tuple *in, t_tuple *normal);
double get_closest(double *t);
t_material *material();
t_color *new_color(double r, double g, double b);
uint64_t get_col(t_color * color);
t_color *to_rgba(double color);
t_world *world();
t_intersect *new_intersect();
t_intersect *world_intersection(t_world *world, t_ray *r);
t_comps *new_comps();
t_comps	*prepare_computing(t_intersect *list, t_ray *r);
t_color *shade_hit(t_world *w, t_comps *comp);
t_color *color_at(t_world *w, t_ray *r);
t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up);
t_ray *ray_for_pixel(t_camera *cam, double x, double y);
t_camera *new_camera(double hsize, double vsize, double fov, t_matrix *transformation);
void render(t_camera *camera, t_world *w);
t_color *compute_ambiant(t_light *light, t_material *m);
bool is_shadow(t_world *w, t_tuple *p);

#endif

/*  ambiant reflection   
	
							I ambiant 
								= 
		ambiant cofficient of the surface (material properity)
									 X 
		I brghitness of the ambiant light in the scene 
*/

/*  diffuse reflection 

					I diffuse
						=
		diffuse cofficient (material properity )
						X
		I intensity of the light source 
						X
		DOT PRODUCT (N normal vector of surface  X  L light direction vector )
		(N . L) the dot product between the normal vector and the light direction ,
		which gives the cosin of the ongle between them ;
*/

/*		Specular reflection 

					I specular
						=
		specular reflection cofficient (material prepority )
						X
		the intensity of the light source
						X
		POW (DOT PRODUCT (R the reflection vector  X  V the view (camera ) direction vector ))) n
		POW ((R . V), n)  dot product betwene the reflection vector and the view direction, 
		raised to the power of n the PHONG EXPENONT , wich control the the sharpness of the specular highlight ;


*/


/*       THE PHONG REFLECTION EQUATION 

		I total = Iambiant + I diffuse + I specular;
		

*/


/*

Vanishing Points: no9tat talashi 
Field of View (FOV) : zawiya ro2ya gedma kabret katzad ro2ya 7edha 180;

*/