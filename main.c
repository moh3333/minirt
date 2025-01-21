/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 18:01:19 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minirt.h"

int main()
{
	t_spher *floor = spher(cpv(0,0,0,1), 1, 0, scal_mat(10,0.01,10));
	floor->material->color = new_color(1,0.9,0.9);
	floor->material->specular = 0.0;
	t_spher *left_wall = spher(cpv(0,0,0,1), 1, 1, mul_mat(transl_mat(0,0,5),mul_mat(rotat_matrix(-(M_PI/4), 'y'), mul_mat(rotat_matrix((M_PI/2), 'x'), scal_mat(10,0.01,10)))));
	left_wall->material = floor->material;
	t_spher *right_wall = spher(cpv(0,0,0,1), 1, 1, mul_mat(transl_mat(0,0,5),mul_mat(rotat_matrix((M_PI/4), 'y'), mul_mat(rotat_matrix((M_PI/2), 'x'), scal_mat(10,0.01,10)))));
	right_wall->material = floor->material;
	t_spher *middle = spher(cpv(0,0,0,1), 1, 3,transl_mat(-0.5,1,0.5));
	middle->material->color = new_color(0.1,1,0.5);
	middle->material->diffuse = 0.7;
	middle->material->specular = 0.3;
	t_spher *right = spher(cpv(0,0,0,1),1,4,mul_mat(transl_mat(1.5,0.5,-0.5), scal_mat(0.5,0.5,0.5)));
	right->material->color = new_color(0.5,1,0.1);
	right->material->diffuse = 0.7;
	right->material->specular = 0.3;
	t_spher *left = spher(cpv(0,0,0,1), 1,5,mul_mat(transl_mat(-1.5, 0.33, -0.75), scal_mat(0.33,0.33,0.33)));
	left->material->color = new_color(1,0.8,0.1);
	left->material->diffuse = 0.7;
	left->material->specular = 0.3;
	t_light *light = light_source(cpv(-10,10,-10, 1), new_color(1,1,1), 1);
	t_camera *camera = new_camera(1000, 1000, M_PI/3, view_transformation(cpv(0,1.5,-5,1),cpv(0,1,0,1), cpv(0,3,0,0)));
	t_world *w = world();
	w->object_count = 6;
	w->light[0].position = light->position;
	w->light[0].color = light->color;
	w->light[0].brightness = light->brightness;
	w->object[1].shape = floor;
	w->object[1].type = SPHER;
	w->object[0].shape = left_wall;
	w->object[0].type = SPHER;
	w->object[2].shape = right_wall;
	w->object[2].type = SPHER;
	w->object[3].shape = middle;
	w->object[3].type = SPHER;
	w->object[4].shape = right;
	w->object[4].type = SPHER;
	w->object[5].shape = left;
	w->object[5].type = SPHER;
	// w->object[6].shape = NULL;
	render(camera, w);
}


	// printf("middle color:  r %f/  g %f  b %f \n", middle->material->color->r,middle->material->color->g,middle->material->color->b );





// int main()
// {
// 	t_material *m = material();
// 	m->color = new_color(1.0,1.0,1.0);
// 	t_tuple *eyev = cpv(0, sqrt(2)/2, -(sqrt(2)/2), 0);
// 	t_tuple *normalv = cpv(0, 0, -1, 0);
// 	t_tuple *pos = cpv(0,0,0,1);
// 	t_light *light = light_source(cpv(0,0,-10,1),new_color(1.0,1.0,1.0), 1);
// 	unsigned int  result = li(m, light, pos, eyev, normalv);
// }

// int main()
// {
// 	t_world *wo;
// 	t_light *light = light_source(cpv(-10,10,-10,1), new_color(1.0,1.0,1.0), 1.0);
// 	t_spher *s1 = spher(cpv(0,0,0,1), 1, 0, i_mat()) ;
// 	t_spher *s2 = spher(cpv(0,0,0,1), 1, 1, scal_mat(0.5,0.5,0.5));
// 	s1->material->color = new_color(0.8,1.0,0.6);
// 	s2->material->color = new_color(2.0,9.0,0.5);
// 	s1->material->diffuse = 0.7;
// 	s1->material->specular = 0.2;
// 	s1->material->ambiant = 1.0;
// 	s2->material->ambiant = 1.0;
// 	wo = world();
// 	wo->light[0] = *light;
// 	wo->object[0].shape = s1;
// 	wo->object[0].type = SPHER;
// 	wo->object[1].shape = s2;
// 	wo->object[1].type = SPHER;
// 	wo->object[2].shape = NULL;
// 	wo->object_count = 2;
// 	double vsize = 200;
// 	double hsize = 125;
// 	double fov = M_PI / 2;
// 	t_camera *camera = new_camera(hsize, vsize, fov, i_mat());
// 	printf("%f\n", camera->pixel_size);
	// t_ray *r = ray(cpv(0,0,0.75,1), cpv(0,0,-1,0));
	// t_color *col = color_at(wo, r);
	// t_tuple *from = cpv(1,3,2,1);
	// t_tuple *to = cpv(4,-2,8,1);
	// t_tuple *up = cpv(1,1,0,1);
	// t_matrix *d = view_transformation(from, to, up);
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
	// printf("r %f  g %f  b %f\n", col->r, col->g, col->b); 
	// printf("comps->t %f\n", comps->t);
	// printf("comps->object->type %d\n", comps->object->type);
	// printf("comps->point %f , %f , %f \n", comps->point->x, comps->point->y, comps->point->z);
	// printf("comps->eyev  %f , %f , %f \n", comps->eyev->x, comps->eyev->y, comps->eyev->z);
	// printf("comps->normalv  %f , %f , %f \n", comps->normalv->x, comps->normalv->y, comps->normalv->z);
// }
// // int main()
// {
// 	double wall_size = 7.0;
// 	double wall_z = 10;
// 	double canvas_pixels = 800;
// 	double pixel_size = wall_size / canvas_pixels;
// 	double half = wall_size / 2;
// 	t_light *light = light_source(cpv(0,0,-50, 1), new_color(1.0,1.0,1.0), 0.8);
// 	t_spher *sph = spher(cpv(0,0,0,1), 1, 0, i_mat());  //unit spher
// 	// sph->transform = transl_mat(0,0,10);
// 	sph->material = material();
// 	sph->material->color = new_color(1.0,0.2,1.0);
// 	// double d[6] = {1,0,1,0,0,0};
// 	// sph->transform = skew_mat(d);
// 	void *mlx = mlx_init(800, 800, "test", 1);
// 	t_tuple *camera_origine = cpv(0,0,-5,1);
// 	mlx_image_t *image = mlx_new_image(mlx, canvas_pixels, canvas_pixels);
// 	for(double y = 0; y < canvas_pixels; y++){
// 		double world_y = half - (pixel_size * y);
// 		for(double x = 0; x < canvas_pixels; x++){
// 			double world_x = -half + (pixel_size * x);
// 			t_tuple *pixel_position = cpv(world_x, world_y, wall_z, 0);
// 			t_ray *r = ray(camera_origine, Normalize(pixel_position));
// 			t_intersect *i = intersect(r, sph);
// 			if (i &&  hit(i->t))
// 			{
// 				double t = get_closest(i->t);
// 				t_color *color = compute_lightning(sph->material, light, position(r, t),opp(Normalize(r->d)), normal_at(sph, position(r, t)));
// 				mlx_put_pixel(image, x, y, get_col(color));
// 			}
// 			else
// 				mlx_put_pixel(image, x, y, BLACK);
// 		}
// 	}
// 	mlx_image_to_window(mlx, image, 0, 0);
// 	mlx_loop(mlx);
// }
// int main()
// {
// 	double wall_size = 70.0;
// 	double wall_z = 100;
// 	double canvas_pixels = 1000;
// 	double pixel_size = wall_size / canvas_pixels;
// 	double half = wall_size / 2;
// 	t_spher *sph = spher(cpv(0,0,0,1), 1, 0);  //unit spher
// 	sph->material = material();
// 	sph->material->color = new_color(1.0,0.2,1.0);
// 	t_color *color;
// 	t_light *light = light_source(cpv(-10,10,-10, 1), new_color(1.0,1.0,1.0), 0.8);
// 	// double d[6] = {1,0,0,0,0,0};
// 	// sph->transform = skew_mat(d);
// 	void *mlx = mlx_init(1000, 1000, "test", 1);
// 	t_tuple *camera_origine = cpv(0,0,-10,1);
// 	mlx_image_t *image = mlx_new_image(mlx, canvas_pixels, canvas_pixels);
// 	for(double y = 0; y < canvas_pixels; y++){
// 		double world_y = half - (pixel_size * y);
// 		for(double x = 0; x < canvas_pixels; x++){
// 			double world_x = -half + (pixel_size * x);
// 			t_tuple *pixel_position = cpv(world_x, world_y, wall_z, 1);
// 			t_ray *r = ray(camera_origine, Normalize(tpl_o(pixel_position, camera_origine, '-')));
// 			t_intersect *i = intersect(r, sph);
// 			if (i &&  hit(i->t))
// 			{
// 				double t = get_closest(i->t);
// 				color = compute_lightning(sph->material, light, position(r, t),opp(Normalize(r->d)), normal_at(sph, position(r, t)));
// 				mlx_put_pixel(image, x, y, get_col(colors_operation(color, sph->material->color, '*')));	
// 			}
// 			else
// 				mlx_put_pixel(image, x, y, BLACK);
// 		}
// 	}
// 	mlx_image_to_window(mlx, image, 0, 0);
// 	mlx_loop(mlx);
// }

// int main()
// {
// 	t_tuple *eyev = cpv(0,0,-1,0);
// 	t_tuple *normalv = cpv(0,0,-1,0);
// 	t_material	*m =material();
// 	m->color = new_color(1,1,1);
// 	t_tuple *position = cpv(0,0,0,1);
// 	t_light *light = light_source(cpv(0,0,10,1), new_color(1.0,1.0,1.0), 1);
// 	t_color *color = compute_lightning(m, light, position, eyev, normalv);
// 	printf("r = %f  g = %f  b = %f\n", color->r, color->g, color->b);
// }