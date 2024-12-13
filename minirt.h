/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:22 by mthamir           #+#    #+#             */
/*   Updated: 2024/12/12 17:10:55 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <libc.h>
#include <math.h>
#include <mlx.h>

#ifndef EPSILON
	#define	EPSILON 0.00001
#endif

typedef struct s_color	{
	double r;
	double g;
	double b;
}	t_color;

typedef struct s_tuple	{
	double x;
	double y;
	double z;
	double w;
} 	t_tuple;



#endif