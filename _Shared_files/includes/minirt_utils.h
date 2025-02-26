/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:17:54 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:45:46 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_UTILS_H
#define MINIRT_UTILS_H

#include "structs.h"

double	add(double a, double b);
double	sub(double a, double b);
double	mul(double a, double b);
double	divi(double a, double b);
double	sq(double num);
t_intersect *new_intersect(void);
t_material *material(void);

t_camera	*new_camera(double hsize, double vsize, double fov, t_matrix *tr);
t_matrix	*view_transformation(t_tuple *from, t_tuple *to, t_tuple *up);
t_color	*new_color(double r, double g, double b);
void	init_camera(char **line, int exist, t_rt *rt);
void	init_ambiant(char **line, int exist, t_rt *rt);
uint64_t	get_col(t_color *color);
t_color	*colors_operation(t_color *a, t_color *b, double (*f) (double a, double b));
t_color	*color_s_mul(t_color *a, double scalar);
t_color	*to_rgba(double color);
void	swap(double *a, double *b);
void	*intersect_between_bounds(double arr[4], t_ray *r_ob_space, t_cylinder *cyl, t_intersect *ret);
t_intersect	*cyl_intersect(t_ray *r, t_cylinder *cyl);
int	check_cap(t_ray *r, double t);
void	intersect_caps_cyl(t_cylinder *cyl, t_ray *r, double *t1, double *t2);
t_cylinder	*cylinder(double *trunc, int id, t_matrix *tr);
t_tuple	*normal_at_cyl(t_cylinder *cyl, t_tuple *p_);
t_matrix	*inverse(t_matrix *a);
double	invertible(t_matrix *a);
double	determinant(t_matrix *a);
double	cofactor(t_matrix *a, int row, int col);
double	det_3(t_3_3 *a);
t_3_3	*sub_m3(t_matrix *a, int row, int col);
double	ft_minor(t_3_3 *a, int row, int col);
double	cof_sign(int r, int c);
double	cof_3(t_3_3 *a, int row, int col );
t_2_2	*sub_m2(t_3_3 *a, int row, int col);
double	det_2(t_2_2 *a);
t_matrix	*i_mat(double diagonal);
t_matrix	*transl_mat(double x, double y, double z);
t_matrix	*scal_mat(double x, double y, double z);
t_matrix	*transpose(t_matrix *a);
t_matrix	*mul_mat(t_matrix *a, t_matrix *b);
t_tuple	*tup_mat_mul(t_matrix *mtx, t_tuple *tpl);
t_matrix	*get_rotat_matrice(t_tuple *normal);
t_tuple	*char_to_vec(char *cam_line, int type);
t_color	*char_to_color(char *s);
double	char_to_double(char *s);
void	print_error(char *error);
void	*ft_malloc(size_t size, int flag);
int	check_for_nl(char	**buff);
char	*get_next_line(int fd);

void	check_extension(char *file_name);
t_line	*parse_file(char *file_name);
t_line	*get_rt_lines(int fd);
char	**split_line(char *s, char c, char c1);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int	all_spaces(char *s);
bool	ft_strcmp(char *s1, char *s2);
char	*ft_copy(char *s1, char *s2, int i);
int	is_float(char *s);
int	ft_strstrlen(char **str);
t_intersect	*pl_intersect(t_ray *r1, t_plane *pl);
t_plane	*plane(int id, t_matrix *tr);
t_ray	*ray(t_tuple origine, t_tuple direction);
t_ray	*transform(t_ray *t, t_matrix *mat);
t_ray	*ray_for_pixel(t_camera *cam, double x, double y);
t_intersect	*intersect(t_ray *ray, t_spher *sph);
t_spher	*spher(t_tuple *center, double raduis, int id, t_matrix *tr);
t_tuple	*normal_at(t_spher *sph, t_tuple *point);
t_tuple	*position(t_ray *ray, double distance);
t_tuple	*reflect(t_tuple in, t_tuple normal);
double	dot_p(t_tuple a, t_tuple b);
t_tuple	*cross_p(t_tuple a, t_tuple b);
t_intersect	*get_first_intersect(t_intersect *list, t_ray *r);
double	get_closest(double *t);
double	hit(double *arr);
double	radians(double degrees);
t_tuple	*scalar(t_tuple a, double scalar);
double	magnitude(t_tuple a);
t_tuple	*cpv(double x, double y, double z, double p_v);
void	ch_pv(t_tuple *a, double x, double y, double z);
t_tuple	*tpl_o(t_tuple a, t_tuple b, double (*f)(double p1, double p2));
void	opp(t_tuple *a);
void	normalize(t_tuple *a);

#endif