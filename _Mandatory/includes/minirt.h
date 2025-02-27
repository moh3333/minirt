/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:22 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 17:12:46 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include "../../_Shared_files/includes/minirt_utils.h"


void	parse_init_structs(t_line *l, t_rt *rt);
void	init_struct(char **line, t_rt *rt);
void	init_objects(char **line, t_rt *rt);
void	init_light(char **line, int exist, t_rt *rt);
void	init_spher(char **line, t_rt *rt, int id);
void	init_plane(char **line, t_rt *rt, int id);
void	init_cylinder(char **line, t_rt *rt, int id);
t_world	*world(void);
void	init_ambiant(char **line, int exist, t_rt *rt);
void	init_camera(char **line, int exist, t_rt *rt);
t_light	*light_source(t_tuple *position, t_color *color);
t_material	*material(void);
t_color	*shade_hit(t_world *w, t_comps *comp);
t_color	*compute_lightning(t_material *m, \
				t_light *light, t_tuple *pos, t_tuple *normalv);
t_intersect	*new_intersect(void);
t_comps	*new_comps(void);
bool	in_shadow(t_world *w, t_comps *comp);
void	is_sphere(t_comps *comp);
t_comps	*prepare_computing(t_intersect *list, t_ray *r, t_world *w);
t_color	*color_at(t_world *w, t_ray *r);
void	handle_keys(mlx_key_data_t keydata, void *param);
void	handle_mlx_window(t_rt *rt, mlx_image_t *image);
void	render(t_rt *rt);
t_intersect	*world_intersection(t_world *world, t_ray *r);
t_intersect	*get_first_intersect(t_intersect *list, t_ray *r);
double	get_closest(double *t);
double	hit(double *arr);

#endif
