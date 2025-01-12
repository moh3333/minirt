/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:28:54 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:32:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* creat a new sphere object */
t_spher *spher(t_tuple *center, double raduis, int id)
{
	t_spher *ret;

	ret = ft_malloc (sizeof(t_spher));
	if (!ret)
		return (NULL);
	ret->c = center;
	ret->r = raduis;
	ret->id = id;
	ret->transform = i_mat();
	ret->material = material();
	return (ret);
}

/* get the normal vector on a point on the spher*/
t_tuple *normal_at(t_spher *sph, t_tuple *point)
{
	t_tuple *object_p;
	t_tuple *object_normal;
	t_tuple *world_normal;

	object_p = tup_mat_mul(inverse(sph->transform), point);
	object_normal = tpl_o(object_p, cpv(0,0,0,1), '-');
	world_normal = tup_mat_mul(transpose(inverse(sph->transform)), object_normal);
	world_normal->w = 0;
	return (Normalize(world_normal));
}

/* get the element of the quadratiq equation */
static double *eq_inter(t_ray *ray1 , t_spher *spher)
{
	double		*arr;

	arr = ft_malloc (4 * sizeof (double));
	if (!arr)
		return (NULL);
	arr[0] = Dot_p(ray1->d, ray1->d);
	arr[1] = 2.0 * (Dot_p(ray1->o, ray1->d));
	arr[2] = (Dot_p(ray1->o, ray1->o) - sq(spher->r));
	arr[3] = sq(arr[1]) - (4 * (arr[0] * arr[2]));
	return (arr);
}

/* check intersection between a ray and a spher */
t_intersect	*intersect(t_ray *ray, t_spher *sph)
{
	t_intersect *inter;
	t_ray *ray1;
	double *arr;

	ray1 = transform(ray, inverse(sph->transform));
	arr = eq_inter(ray1, sph);
	if (!arr)
		return (NULL);
	inter = ft_malloc(sizeof(t_intersect));
	if (!inter)
		return (NULL);
	inter->t = new_t();
	inter->t[0] = (-arr[1] - sqrt(arr[3])) / (2 * (arr[0]));
	inter->t[1] = (-arr[1] + sqrt(arr[3])) / (2 * (arr[0]));
	inter->object = sph;
	inter->ray = ray1;
	if (arr[3] < 0)
		return (NULL);
	return (inter);
}

/* set the transformation matrix on sphere struct */
void	set_tranform(t_spher *sph, t_matrix *mat)
{
	*sph->transform = *mat;
}