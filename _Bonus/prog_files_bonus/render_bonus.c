/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:22:21 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/11 21:30:12 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"

uint64_t	color_at(t_world *w, t_ray *r)
{
	t_tuple	eyev;
	t_color	*col;

	eyev = r->d;
	opp(&eyev);
	col = shade_hit(w, prepare_computing(world_intersection(w, r), r), &eyev);
	if (!col)
		return (BLACK);
	return (get_col(col));
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	mlx_t	*p;

	p = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(p);
}

void	handle_mlx_window(t_rt *rt, mlx_image_t *image)
{
	mlx_image_to_window(rt->cam->mlx, image, 0, 0);
	mlx_key_hook(rt->cam->mlx, handle_keys, rt->cam->mlx);
	mlx_loop(rt->cam->mlx);
	mlx_terminate(rt->cam->mlx);
	exit(0);
}

void	render(t_rt *rt)
{
	double			x;
	double			y;
	mlx_image_t		*image;
	uint64_t		col;

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
			mlx_put_pixel(image, x, y, col);
		}
	}
	handle_mlx_window(rt, image);
}

int	main(int ac, char **av)
{
	t_line	l;
	t_rt	rt;

	if (ac == 2)
	{
		ft_malloc(0, INIT);
		rt.world = world();
		l = *parse_file(av[1]);
		if (!l.line[0])
			return (1);
		parse_init_structs(&l, &rt);
		if (!rt.cam)
			return (print_error(NO_CAM), 1);
		if (!rt.world->ambiant_color)
			return (print_error(NO_AMB), 1);
		render(&rt);
	}
}
