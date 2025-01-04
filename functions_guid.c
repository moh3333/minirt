/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_guid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:45:21 by mthamir           #+#    #+#             */
/*   Updated: 2024/12/30 14:45:04 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
double radians(double degrees)
{
	return ((degrees / 180) * π);
}
int main()
{
	void *mlx = mlx_init(1000, 1000, "title", 1);
	mlx_image_t *image = mlx_new_image(mlx, 1000, 1000);
	double x = 0;
	double y = 0;
	double beta = 0;
	double f = 0;
	double color = 0xFF0F0F0; 
	double raduis = 400;
	double center_x = 450;
	double center_y = 450;
	while (f < raduis)
	{
		x = 0;
		y = 0;
		beta = 0;
		while (beta <= 360)
		{
			x = center_x + f * cos(radians(beta));
			y = center_y + f * sin(radians(beta));
			mlx_put_pixel(image, x, y, color);
			beta += 0.01;
		}
		f += 1;
	}
	mlx_put_string(mlx,  "terere m3a bnat tchmara ... ", 400, 100);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
}