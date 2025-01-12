/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:33:09 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/12 15:33:39 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light *light_source(t_tuple *position, t_color *color, double brightness)
{
	t_light *light;

	light = ft_malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->brightness = brightness;
	light->color = color;
	return (light);
}