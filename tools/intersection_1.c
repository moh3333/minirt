/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:04:45 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 18:25:48 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_world *world()
{
	t_world *world;

	world = ft_malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	return (world);
}

static void add_to_list(t_intersect **head, t_intersect *new)
{
	t_intersect *tmp;

	if (!*head)
    {
        *head = new;
        return;
    }
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_intersect *world_intersection(t_world *world, t_ray *r)
{
	t_intersect *head;
	t_intersect *inter;
	int i;

	i = 0;
	inter = NULL;
	head = NULL;
	while (i < world->object_count)
	{
		if (world->object[i].type == SPHER)
			inter = intersect(r, world->object[i].shape);
		if (inter)
			add_to_list(&head, inter);
		i++;
	}
	return (head);
}

t_intersect *get_first_intersect(t_intersect *list, t_ray *r)
{
    t_intersect *tmp = list;
    t_intersect *ret = new_intersect(); 

    ret->ray = r;
    ret->t[0] = HUGE_VAL;
    while (tmp) {
		if (hit(tmp->t))
		{
			tmp->t[0] = get_closest(tmp->t);
        	if (tmp->t[0] < ret->t[0]) 
			{
            	ret->t[0] = tmp->t[0];
            	ret->object = tmp->object;
			}
        }
        tmp = tmp->next;
    }
    if (ret->object == NULL)
        return NULL;
    return ret;
}

t_color *shade_hit(t_world *w, t_comps *comp)
{
	if (is_shadow(w, comp->point))
		return (compute_ambiant(w->light, comp->object->shape->material));
	return (compute_lightning(comp->object->shape->material, w->light, comp->point, comp->eyev, comp->normalv));
}

t_comps	*prepare_computing(t_intersect *list, t_ray *r)
{
	t_comps *comp;
	t_intersect *inter;
	
	comp = new_comps();
	inter = get_first_intersect(list, r);
	
	comp->t = inter->t[0];
	comp->object = inter->object;
	comp->point  = position(r, comp->t);
	comp->eyev = opp(r->d);
	comp->normalv = normal_at(comp->object->shape, comp->point);
	if (Dot_p(comp->normalv, comp->eyev) < EPSILON)
	{
		comp->inside = true;
		comp->normalv = opp(comp->normalv);
	}
	else
		comp->inside = false;
	return (comp);
}

t_color *color_at(t_world *w, t_ray *r)
{
	t_intersect *ret = world_intersection(w, r);
	if (!ret)
		return (new_color(0.0,0.0,0.0));
	return (shade_hit(w, prepare_computing(ret, r)));
}

t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_matrix *ret;
	t_tuple *forward = Normalize(tpl_o(to , from, '-'));
	t_tuple *left = Cross_p(forward, Normalize(up));
	t_tuple *true_up = Cross_p(left, forward);
	
	ret = i_mat();
	ret->matrix[0][0] = left->x;
	ret->matrix[0][1] = left->y;
	ret->matrix[0][2] = left->z;
	ret->matrix[1][0] = true_up->x;
	ret->matrix[1][1] = true_up->y;
	ret->matrix[1][2] = true_up->z;
	ret->matrix[2][0] = -forward->x;
	ret->matrix[2][1] = -forward->y;
	ret->matrix[2][2] = -forward->z;
	return (mul_mat(ret, transl_mat(-from->x, -from->y, -from->z)));
}

t_ray *ray_for_pixel(t_camera *cam, double x, double y)
{
	double x_offset = (x + 0.5) * cam->pixel_size;
	double y_offset = (y + 0.5) * cam->pixel_size;
	double world_x = cam->half_width - x_offset;
	double world_y = cam->half_hight - y_offset;
	t_tuple *pixel = tup_mat_mul(cam->transform_inverse , cpv(world_x,world_y,-1,1));
	t_tuple *origine = tup_mat_mul(cam->transform_inverse , cpv(0,0,0,1));
	t_tuple *direction = Normalize(tpl_o(pixel, origine, '-'));
	return (ray(origine, direction));
}

void render(t_camera *camera, t_world *w)
{
	double x = 0;
	double y = 0;
	t_ray *r;
	t_color *col;
	camera->mlx =  mlx_init(camera->horizontal_size, camera->vertical_size, "test", 1);
	mlx_image_t *image = mlx_new_image(camera->mlx ,camera->horizontal_size, camera->vertical_size);
	while (y < camera->vertical_size)
	{
		x = 0;
		while (x < camera->horizontal_size)
		{
			r = ray_for_pixel(camera, x, y);
			col = color_at(w, r);
			mlx_put_pixel(image, x, y, get_col(col));
			x++;
		}
		y++;
	}
	mlx_image_to_window(camera->mlx, image, 0, 0);
	mlx_loop(camera->mlx);
}

bool is_shadow(t_world *w, t_tuple *p)
{
	t_tuple *shadow_ray = tpl_o(w->light->position, p, '-');
	double distance = magnitude(shadow_ray);

	t_ray *r = ray(p, Normalize(shadow_ray));
	t_intersect *inter = get_first_intersect(world_intersection(w, r), r);
	if (inter && inter->t[0] < distance)
		return (true);
	return (false);
}