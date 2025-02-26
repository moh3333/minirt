/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:05:16 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 16:28:18 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_FILES_H
# define SHARED_FILES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../../MLX42/include/MLX42/MLX42.h"
#include "macros.h"

typedef struct s_pool t_pool;
typedef struct s_pool
{
	void *block;
	size_t offset;
}	t_pool;

typedef struct s_line{
	char *line[200];
	int count;
}	t_line ;

typedef struct s_color	{
	double r;
	double g;
	double b;
}	t_color;


typedef struct s_material
{
	t_color color;
	double	checker;
	t_color pattern_color;
}	t_material;


typedef struct s_tuple	{
	double x;
	double y;
	double z;
	double w;
} 	t_tuple;


typedef struct s_light
{
	t_tuple position;
	t_color color;
}	t_light;

typedef struct s_matrix{
	double matrix[4][4];
}	t_matrix;

typedef struct s_2_2{
	double matrix[2][2];
}	t_2_2;

typedef struct s_3_3{
	double matrix[3][3];
}	t_3_3;

typedef struct s_ray
{
	t_tuple o;
	t_tuple d;
}	t_ray;

typedef struct s_spher
{
	double	r;
	int		id;
	t_matrix *transform;
	t_tuple	*c;
	t_color color;
	t_material *material;
	t_matrix *inverse_m;
	t_matrix *transpose_in;

}	t_spher;

typedef struct s_plane
{
	int		id;
	t_tuple	*c;
	t_color color;
	t_material *material;
	t_matrix *transform;
	t_matrix *inverse_m;
	t_matrix *transpose_inverse;
	t_tuple *normalv;
}	t_plane;

typedef struct s_cylinder
{
	int		id;
	t_tuple *centre;
	double min;
	double max;
	t_color color;
	t_material *material;
	t_matrix *transform;
	t_matrix *inverse_m;
	t_matrix *transpose_inverse;
}	t_cylinder;

typedef struct s_cone
{
	int		id;
	t_tuple *centre;
	double min;
	double max;
	t_color color;
	t_material *material;
	t_matrix *transform;
	t_matrix *inverse_m;
	t_matrix *transpose_inverse;
}	t_cone;

typedef struct s_object
{
	int type;
	t_spher shape;
	t_plane shape_pl;
	t_cylinder shape_cyl;
	t_cone shape_co;
} t_object;

typedef struct s_intersect t_intersect;
typedef struct s_intersect
{
	t_ray *ray;
	t_object object;
	double t[2];
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
	t_tuple *origine;
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

typedef struct s_comps
{
	double t;
	t_object object;
	t_tuple *point;
	bool shadow;
	t_tuple *eyev;
	t_tuple *normalv;
	bool inside;
}	t_comps;


typedef struct s_world
{
	int object_count;
	int light_count;
	t_light light[200];
	t_object object[200];
	t_color *ambiant_color;
	double ambiant_coff;
}	t_world;

typedef struct s_rt
{
	t_world *world;
	t_camera *cam;
}	t_rt;
#endif