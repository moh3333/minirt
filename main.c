/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:39:20 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minirt.h"



int main()
{
	double hight = 600.0;
	double width = 600.0;
	double aspect_ratio = hight / width;
	double y_center = hight / 2.0;
	double x_center = width / 2.0;
	t_spher *sph = spher(cpv(0,0,0,1), 1, 0);  //unit spher
	sph->material = material();
	double color = 0xFFFFFF;
	double d[] = {1,0,0,0,0,0};
	sph->transform = mul_mat( scal_mat(50, 50, 1), skew_mat(d));
	void *mlx = mlx_init(600, 600, "test", 1);
	t_tuple *camera_origine = cpv(0,0,-10,1);
	mlx_image_t *image = mlx_new_image(mlx, 600, 600);
	mlx_image_to_window(mlx, image, 0, 0);
	for(double y = 0; y < width; y++){
		double world_y = y_center - (aspect_ratio * y);
		for(double x = 0; x < hight; x++){
			double world_x = -x_center + (aspect_ratio * x);
			t_tuple *pixel_position = cpv(world_x, world_y, 20, 1);
			t_ray *r = ray(camera_origine, Normalize(tpl_o(pixel_position, camera_origine, '-')));
			t_intersect *i = intersect(r, sph);
			if (i &&  hit(i->t))
				mlx_put_pixel(image, x, y, color);
				
			else
				mlx_put_pixel(image, x, y, BLACK);
			
		}
	}
	mlx_loop(mlx);
}
