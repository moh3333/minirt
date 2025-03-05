/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:22 by mthamir           #+#    #+#             */
/*   Updated: 2025/03/02 21:16:05 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../../_Shared_files/includes/minirt_utils.h"

void		parse_init_structs(t_line *l, t_rt *rt);
t_color		*spher_texter(t_spher *sp, t_material *m, t_comps *comp);
void		init_struct(char **line, t_rt *rt);
void		init_objects(char **line, t_rt *rt);
void		init_light(char **line, t_rt *rt);
void		init_spher(char **line, t_rt *rt, int id);
void		init_checker(t_plane *pl, char *scl, char *line);
void		init_plane(char **line, t_rt *rt, int id);
void		init_cylinder(char **line, t_rt *rt, int id);
void		init_cone(char **line, t_rt *rt, int id);
t_cone		*cone(double *trunc, int id, t_matrix *tr);
t_tuple		*normal_at_co(t_cone *co, t_tuple *p_);
void		*first_algo(double arr[4], t_intersect *ret);
void		*intersect_between_co_bounds(double arr[4], t_ray *r_ob_space, \
								t_cone *co, t_intersect *ret);
t_intersect	*cone_intersect(t_ray *r, t_cone *co);
void		intersect_caps_co(t_cone *co, t_ray *r, double *t1, double *t2);
t_world		*world(void);
t_light		*light_source(t_tuple *position, t_color *color);
t_material	*material(void);
t_color		*compute_specular(t_light *light, \
		t_tuple *lightv, t_tuple *normalv, t_tuple *eyev);
t_color		*check_pattern(t_tuple *p, t_material *m);
t_color		*shade_hit(t_world *w, t_comps *comp, t_tuple *eyev);
t_color		*compute_lightning_b(t_light *light, \
			t_comps *comp, t_tuple *eyev, t_color *col);
t_intersect	*new_intersect(void);
t_comps		*new_comps(void);
bool		in_shadow(t_world *w, t_comps *comp, int i);
void		is_sphere(t_comps *comp);
t_comps		*prepare_computing(t_intersect *list, t_ray *r);
uint64_t	color_at(t_world *w, t_ray *r);
void		handle_keys(mlx_key_data_t keydata, void *param);
void		handle_mlx_window(t_rt *rt, mlx_image_t *image);
void		render(t_rt *rt);
t_intersect	*world_intersection(t_world *world, t_ray *r);

#endif
