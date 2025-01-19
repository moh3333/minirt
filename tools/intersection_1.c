/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:04:45 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/19 17:33:02 by mthamir          ###   ########.fr       */
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
		printf("herehere     %f       %f\n", inter->t[0], inter->t[1]);
		i++;
	}
	return (head);
}

t_intersect	*get_first_intersect(t_intersect *list, t_ray *r)
{
	t_intersect *tmp;
	t_intersect *ret;
	int i = 0;

	tmp = list;
	ret = new_intersect();
	ret->ray = r;
	while (tmp && i < 200)
	{
		if (hit(tmp->t)){
			tmp->t[0] = get_closest(tmp->t);
			i++;
		}
		tmp = tmp->next;
	}
	tmp = list;
	if (!tmp->next)
		return (tmp);
	while(tmp->next)
	{
		if (fmin(tmp->t[0], tmp->next->t[0]) == tmp->t[0]){
			ret->t[0] = tmp->t[0];
			ret->object = tmp->object;
		}
		else{
			ret->t[0] = tmp->next->t[0];
			ret->object = tmp->next->object;
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_color *shade_hit(t_world *w, t_comps *comp)
{
	return (compute_lightning(comp->object->shape->material, w->light, comp->point, comp->eyev, comp->normalv));
}
t_comps	*prepare_computing(t_intersect *list, t_ray *r)
{
	t_comps *comp;
	t_intersect *inter;
	
	comp = new_comps();
	inter = get_first_intersect(list, r);
	
	comp->t = inter->t[0];
	printf("           %f\n", inter->t[0]);
	comp->object = inter->object;
	comp->point  = position(r, comp->t);
	printf("point is   %f %f  %f \n", comp->point->x,comp->point->y,comp->point->z);
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

	ret = transl_mat(from->x, from->y, from->z);
}