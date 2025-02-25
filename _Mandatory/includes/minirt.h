/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:22 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/25 19:46:57 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "structs.h"
#include "macros.h"

/*______________________________parse_____________________________*/
char	*ft_copy(char *s1, char *s2, int i);
int ft_strstrlen(char **str);
int  is_float(char *s);
char	**split_line(char *s, char c, char c1);
char	*get_next_line(int fd);
bool ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
double char_to_double(char *s);
void parse_init_structs(t_line *l, t_rt *rt);
void	init_struct(char **line, t_rt *rt);
void init_objects(char **line, t_rt *rt);
void	init_plane(char **line, t_rt *rt, int id);
t_matrix *get_rotat_matrice(t_tuple *normal);
void init_spher(char **line, t_rt *rt, int id);
void init_light(char **line, int exist ,t_rt *rt);
void init_ambiant(char **line,int exist,t_rt *rt);
t_color *char_to_color(char *s);
void init_camera(char **line, int exist, t_rt *rt);
t_tuple *char_to_vec(char *cam_line, int type);
t_line 	*parse_file(char *file_name);
t_line *get_rt_lines(int fd);
void check_extension(char *file_name);
void print_error(char *error);
void init_cylinder(char **line, t_rt *rt, int id);
int all_spaces(char *s);

/*______________________________exec_____________________________*/
/* creat a point or a vector */
t_tuple	*cpv(double x, double y, double z, double p_v);
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
t_tuple *tpl_o(t_tuple a, t_tuple b , double (*f)(double p1, double p2));
/*get the opposite vector of a given one */
void opp(t_tuple *a);
/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple a, double scalar);
/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple a);
/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
void normalize(t_tuple *a);
/* we use it to compare between two vector direction and knowing the angle between them */
double	dot_p(t_tuple a, t_tuple b);
/* the result is a vector that its perpodicular to both of the two used vectors*/
t_tuple *cross_p(t_tuple a, t_tuple b);
/* get squar of a number */
double	sq(double num);
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b);
/* identity matrix multipliyng by any matrix it gives the same matrix */
t_matrix *i_mat(double diagonal);
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
t_ray *ray(t_tuple origine, t_tuple direction);
/* shows how far the ray travels in (x distance) seconds  (Computing a point from a distance)*/
t_tuple *position(t_ray *ray, double distance);
/* creat a sphere with given enter and raduis */
t_spher *spher(t_tuple *center, double raduis, int id, t_matrix *tr);
/* check rays sphere intersection and fill the t_intersect struct with object type and object and intersection points */
t_intersect	*intersect(t_ray *ray, t_spher *spher);
t_ray *transform(t_ray *t, t_matrix *mat);
/* get the normal vector on a point on the spher*/
t_tuple *normal_at(t_spher *sph, t_tuple *point);
/* colors addition and subtraction */
t_color *colors_operation(t_color *a, t_color *b, double (*f) (double a, double b));
/* colors multiplication with a scalar */
t_color *color_s_mul(t_color *a, double scalar);
/* get diffuse and ambiant color ona apoint */
t_color *compute_lightning(t_material *m, t_light *light, t_tuple *pos, t_tuple *normalv);
void *ft_malloc(size_t size, int flag);
double hit(double *arr);
t_light *light_source(t_tuple *position, t_color *color);
t_tuple *reflect(t_tuple in, t_tuple normal);
double get_closest(double *t);
t_material *material();
t_color *new_color(double r, double g, double b);
uint64_t get_col(t_color * color);
t_color *to_rgba(double color);
t_world *world();
t_intersect *new_intersect();
t_intersect *world_intersection(t_world *world, t_ray *r);
t_comps *new_comps();
t_comps	*prepare_computing(t_intersect *list, t_ray *r, t_world *w);
t_color *shade_hit(t_world *w, t_comps *comp);
t_color *color_at(t_world *w, t_ray *r);
t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up);
t_ray *ray_for_pixel(t_camera *cam, double x, double y);
t_camera *new_camera(double hsize, double vsize, double fov, t_matrix *transformation);
void render(t_rt *rt);
t_intersect *get_first_intersect(t_intersect *list, t_ray *r);
t_intersect *pl_intersect(t_ray *r1, t_plane *pl);
t_plane *plane(int id, t_matrix *tr);
t_tuple *normal_at_cyl(t_cylinder *cyl, t_tuple *p);
t_intersect *cyl_intersect(t_ray *r, t_cylinder *cyl);
t_material *material();
void intersect_caps_cyl(t_cylinder *cyl, t_ray *r, double *t1, double *t2);
void ch_pv(t_tuple *a, double x, double y, double z);
t_cylinder *cylinder(double arr[2], int id, t_matrix *tr);
#endif
