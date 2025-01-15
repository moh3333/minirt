/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/15 16:28:20 by mthamir          ###   ########.fr       */
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
	double hight = 600.0;
	double width = 600.0;
	double aspect_ratio = hight / width;
	double y_center = hight / 2.0;
	double x_center = width / 2.0;
	t_spher *sph = spher(cpv(0,0,0,1), 1, 0);  //unit spher
	sph->material = material();
	sph->material->color = new_color(1.0,0.2,1.0);
	t_color *color;
	t_light *light = light_source(cpv(-10,10,-5, 1), new_color(1.0,1.0,1.0), 1);
	sph->transform = scal_mat(20, 20, 1);
	void *mlx = mlx_init(600, 600, "test", 1);
	t_tuple *camera_origine = cpv(0,0,-5,1);
	mlx_image_t *image = mlx_new_image(mlx, 600, 600);
	for(double y = 0; y < width; y++){
		double world_y = (y_center+0.5) - (aspect_ratio * y);
		for(double x = 0; x < hight; x++){
			double world_x = -(x_center+0.5) + (aspect_ratio * x);
			t_tuple *pixel_position = cpv(world_x, world_y, 20, 1);
			t_ray *r = ray(camera_origine, Normalize(tpl_o(pixel_position, camera_origine, '-')));
			t_intersect *i = intersect(r, sph);
			if (i &&  hit(i->t))
			{
				double t = get_closest(i->t);
				color = compute_lightning(sph->material, light, position(r, t),normal_at(sph, position(r, t)));
				mlx_put_pixel(image, x, y, get_col(colors_operation(color, sph->material->color, '*')));	
			}
			else
				mlx_put_pixel(image, x, y, BLACK);
		}
	}
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
}
