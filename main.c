/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/19 17:08:48 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minirt.h"

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

int main()
{
	t_world *wo;
	t_light *light = light_source(cpv(-10,10,-10,1), new_color(1.0,1.0,1.0), 1.0);
	t_spher *s1 = spher(cpv(0,0,0,1), 1, 0, i_mat()) ;
	t_spher *s2 = spher(cpv(0,0,0,1), 1, 1, scal_mat(0.5,0.5,0.5));
	s1->material->color = new_color(0.8,1.0,0.6);
	s2->material->color = new_color(2.0,9.0,0.5);
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	s1->material->ambiant = 1.0;
	s2->material->ambiant = 1.0;
	wo = world();
	wo->light[0] = *light;
	wo->object[0].shape = s1;
	wo->object[0].type = SPHER;
	wo->object[1].shape = s2;
	wo->object[1].type = SPHER;
	wo->object[2].shape = NULL;
	wo->object_count = 2;
	t_ray *r = ray(cpv(0,0,0.75,1), cpv(0,0,-1,0));
	t_color *col = color_at(wo, r);
	printf("r %f  g %f  b %f\n", col->r, col->g, col->b);
	// printf("comps->t %f\n", comps->t);
	// printf("comps->object->type %d\n", comps->object->type);
	// printf("comps->point %f , %f , %f \n", comps->point->x, comps->point->y, comps->point->z);
	// printf("comps->eyev  %f , %f , %f \n", comps->eyev->x, comps->eyev->y, comps->eyev->z);
	// printf("comps->normalv  %f , %f , %f \n", comps->normalv->x, comps->normalv->y, comps->normalv->z);
}
// int main()
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