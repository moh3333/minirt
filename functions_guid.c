/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_guid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:45:21 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/05 16:09:44 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"




int main()
{
	double wall_size = 7.0;
	double canvas_pixel = 100.0;
	double pixel_size = wall_size / canvas_pixel;
	double half = wall_size / 2.0;
	double  color = 0xFF000;
	t_spher *sph = spher(cpv(0,0,0,1), 1, 0);
	void *mlx = mlx_init(600, 600, "test", 1);
	t_tuple *origine = cpv(0,0,-5,1);
	mlx_image_t *image = mlx_new_image(mlx, 500, 500);
	for(double y = 0; y < canvas_pixel; y++){
		double world_y = half - pixel_size * y;
		for(double x = 0; x < canvas_pixel; x++){
			double world_x = -half + pixel_size * x;
			t_tuple *position = cpv(world_x, world_y, 10, 1);
			t_ray *r = ray(origine, Normalize(tpl_o(position, origine, '-')));
			// t_intersect *i = intersect(sph, r);
			// if (hit(i->t))
			mlx_put_pixel(image, x, y, color);
		}
	}
	mlx_image_to_window(mlx, image, 50, 50);
	mlx_loop(mlx);
}