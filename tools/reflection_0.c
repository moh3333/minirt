/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:35:04 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 14:26:59 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
	return (tpl_o(in, (scalar(normal, mul(Dot_p(in, normal), 2))),  '-'));
}

double get_closest(double *t)
{
	if (t[0] < EPSILON)
		return (t[1]);
	else if (t[1] < EPSILON)
		return (t[0]);
	else if (t[0] < t[1])
		return (t[0]);
	return (t[1]);
}

t_material *material()
{
	t_material *mate = ft_malloc(sizeof(t_material));

	mate->color = new_color(1.0,1.0,1.0);
	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	return (mate);
}

t_color *compute_ambiant(t_light *light, t_material *m)
{
	t_color *effective_color;
	effective_color = colors_operation(color_s_mul(light->color, light->brightness), m->color, '*');
	return (color_s_mul(effective_color, m->ambiant));
}

t_color *compute_diffuse(t_material *m, t_light *light, t_tuple *pos, t_tuple *normalv)
{
	t_tuple *lightv;
	double light_dot_normal;
	lightv = Normalize(tpl_o(light->position, pos, '-'));
	light_dot_normal = Dot_p(lightv,normalv);
	if(light_dot_normal >= EPSILON)
		return (color_s_mul(colors_operation(light->color, m->color, '*'), (m->diffuse * light_dot_normal)));
	return (new_color(0.0,0.0,0.0));
}

t_color *compute_specular(t_material *m, t_light *light, t_tuple *normalv, t_tuple *eyev, t_tuple *pos)
{
	t_tuple *reflectv;
	t_tuple *lightv;
	double factor;
	double reflect_dot_eye;
	lightv = Normalize(tpl_o(light->position, pos, '-')); 
	reflectv = reflect(Normalize(opp(lightv)), normalv);
	reflect_dot_eye = Dot_p(reflectv, eyev);
	if (reflect_dot_eye > EPSILON){
		factor = pow(reflect_dot_eye, m->shininess);
		return (color_s_mul(light->color, (m->specular * factor)));
	}
	return (new_color(0.0,0.0,0.0));

}

t_color *compute_lightning(t_material *m, t_light *light, t_tuple *pos,t_tuple *eyev, t_tuple *normalv)
{
	t_color *ambiant;
	t_color *diffuse;
	t_color *specular;
	specular = new_color(0.0,0.0,0.0);
	ambiant = compute_ambiant(light, m);
	diffuse = compute_diffuse(m, light, pos, normalv);
	specular = compute_specular(m, light, normalv, eyev, pos);
	return (colors_operation(colors_operation(diffuse, ambiant, '+'), specular, '+'));
}