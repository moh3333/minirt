/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:22:21 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/08 13:33:43 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_color	*color_at(t_world *w, t_ray *r)
{
	return (shade_hit(w, prepare_computing(world_intersection(w, r), r, w)));
}

void	handle_keys(mlx_key_data_t keydata, void* param)
{
	mlx_t *p = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(p);
}

void	handle_mlx_window(t_rt *rt, mlx_image_t *image)
{
	mlx_image_to_window(rt->cam->mlx, image, 0, 0);
	mlx_key_hook(rt->cam->mlx, handle_keys, rt->cam->mlx);
	mlx_loop(rt->cam->mlx);
	mlx_terminate(rt->cam->mlx);
	ft_malloc(0, FREE);
}

void	render(t_rt *rt)
{
	double		x;
	double		y;
	mlx_image_t	*image;
	t_color		*col;

	x = -1;
	y = -1;
	rt->cam->mlx = mlx_init(rt->cam->horizontal_size, \
	rt->cam->vertical_size, "MINI_RT_1337", 1);
	image = mlx_new_image(rt->cam->mlx, rt->cam->horizontal_size, \
	rt->cam->vertical_size);
	rt->cam->origine = cpv(rt->cam->transform_inverse->matrix[0][3], \
	rt->cam->transform_inverse->matrix[1][3], \
	rt->cam->transform_inverse->matrix[2][3], 1);
	while (++y < rt->cam->vertical_size)
	{
		x = -1;
		while (++x < rt->cam->horizontal_size)
		{
			col = color_at(rt->world, ray_for_pixel(rt->cam, x, y));
			mlx_put_pixel(image, x, y, get_col(col));
		}
	}
	handle_mlx_window(rt, image);
}
// void f(){system("leaks minirt");}
int	main(int ac, char **av)
{
	t_line	l;
	t_rt	rt;
	// atexit(f);
	rt.world = world();
	if (ac == 2)
	{
		l = *parse_file(av[1]);
		parse_init_structs(&l, &rt);
		render(&rt);
	}
	ft_malloc(0, FREE);
}
