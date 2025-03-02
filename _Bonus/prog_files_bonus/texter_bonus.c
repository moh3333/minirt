/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:18:47 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/28 19:36:21 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minirt_bonus.h"



void bump_maping(t_material *m, t_tuple *obj_point)
{
    double theta, phi, u, v;
    uint8_t *bump;
    double nx;

    normalize(obj_point);
    theta = atan2(obj_point->z, obj_point->x); // [-π, π]
    phi = acos(obj_point->y); // [0, π]

    u = 0.25 +(theta + M_PI) / (2.0 * M_PI); 
    v = (M_PI - phi) / M_PI; 

    u = fmod(u + 1.0, 1.0);
    v = fmod(v + 1.0, 1.0);

    uint32_t t = (uint32_t)(u * (m->bump_map->width - 1));
    uint32_t l = (uint32_t)((1.0 - v) * (m->bump_map->height - 1));

    bump = &m->bump_map->pixels[(l * m->bump_map->width + t) * 4];
    if (!bump)
        return;

    nx = ((bump[0] / 255.0) * 2.0 - 1.0) * 5;

    ch_pv(obj_point, obj_point->x + nx, obj_point->y + nx, obj_point->z);
}
// t_color *spher_texter(t_material *m, t_tuple *point)
// {

//     double theta, phi, u, v;
//     t_color *ll;
//     t_tuple  *obj_point = cpv(point->x,point->y,point->z,point->w);
//     normalize(obj_point);
//     theta = atan2(obj_point->z, obj_point->x); // [-π, π]
//     phi = acos(obj_point->y); // [0, π]

//     u = 0.25 + (theta + M_PI) / (2.0 * M_PI); 
//     v = (M_PI - phi) / M_PI; 

//     printf("v :%f u:%f \n",v,u);
// 	uint32_t t = (uint32_t)((u) * (m->texter->width - 1));
// 	uint32_t l = (uint32_t)((1.0 - v) * (m->texter->height - 1)); 
//     printf("t: %d, l: %d\n", t, l);
// 	uint8_t *textur = &m->texter->pixels[(l * m->texter->width + t) * 4];
    
//     printf("%d :%d : %d \n",textur[0],textur[1],textur[2]);
//     ll = new_color((double)textur[0] / 255.0, (double)textur[1] / 255.0, (double)textur[2] / 255.0);
//     printf("%f :%f : %f \n",ll->r,ll->g,ll->b);
//     return(ll);
// }
// t_tuple *compute_tangent(t_tuple N) {
//     t_tuple up = {1, 0, 0}; 
//     // if (fabs(N.y) > 1) 
//     //     up = (t_tuple){1, 0, 0}; 
//     return (cross_p(up, N));
// }


t_color *spher_texter(t_spher *sp, t_material *m, t_comps *comp)
{
    t_tuple *obj_point;
    double theta, phi, u, v;

    obj_point = tup_mat_mul(sp->inverse_m, comp->point);

    theta = atan2(obj_point->z, obj_point->x); // [-π, π]
    phi = acos(obj_point->y / magnitude(*obj_point)); // [0, π]
    u = 0.25 + (theta + M_PI) / (2.0 * M_PI); 
    v = 1.0 - (phi / M_PI);            
    u = fmax(0.0, fmin(1.0, u));
    v = fmax(0.0, fmin(1.0, v));
    uint32_t x = (uint32_t)(u * (m->texter->width - 1));
    uint32_t y = (uint32_t)((1.0 - v) * (m->texter->height - 1));
    uint8_t *pixel = &m->texter->pixels[(y * m->texter->width + x) * 4];
    return new_color(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0);
}
