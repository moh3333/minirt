/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:05:36 by mthamir           #+#    #+#             */
/*   Updated: 2025/01/21 17:59:51 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*if p_v is (1) creat point if its 0 creat vector */

t_tuple *cpv(double x, double y, double z, double p_v)
{
	t_tuple *a;

	a = ft_malloc(sizeof(t_tuple));
	if (!a)
		return (NULL);
	a->x = x;
	a->y = y;
	a->z = z;
	a->w = p_v;
	return (a);
}

/* if it return (0) it's a point else it's a vector */
int ispoint(t_tuple *a)
{
	return ((a->w == 1));
}

/*operation two tuples */
t_tuple *tpl_o(t_tuple *a, t_tuple *b , char op)
{
	t_tuple *ret;
	double	(*f)(double p1, double p2);

	f = NULL;
	ret = NULL;
	if(op == '+')
		f = add;
	else if(op == '-')
		f = sub;
	ret = ft_malloc (sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = f(a->x, b->x);
	ret->y = f(a->y, b->y);
	ret->z = f(a->z, b->z);
	ret->w = f(a->w, b->w);
	return (ret);
}

/*get the opposite vector if the given is from a to b it will return the vector from b to a */
t_tuple *opp(t_tuple *a)
{
	t_tuple *opp;

	opp = ft_malloc (sizeof (t_tuple));
	if (!opp)
		return (NULL);
	opp->x = -a->x;
	opp->y = -a->y;
	opp->z = -a->z;
	opp->w = -a->w;
	return (opp);
}

/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple *a, double scalar)
{
	t_tuple *ret;

	ret = ft_malloc(sizeof (t_tuple));
	if (!ret)
		return (NULL);
	ret->x = (mul(a->x, scalar));
	ret->y = (mul(a->y, scalar));
	ret->z = (mul(a->z, scalar));
	ret->w = a->w;
	return (ret);
}