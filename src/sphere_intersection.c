/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:02:52 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:22:10 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		solve_sphere(double x[2], t_vector origin, t_vector direction, t_figures *lst)
{
	double		disc;
	t_vector	oc;
	double		k[3];

	oc = vector_substract(origin, lst->figure.sphere.center);
	k[0] = vector_dot(direction, direction);
	k[1] = 2 * vector_dot(direction, oc);
	k[2] = vector_dot(oc, oc) - lst->figure.sphere.radius * lst->figure.sphere.radius;
	disc = k[1] * k[1] - (4 * k[0] * k[2]);
	if (disc < 0)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return ;
	}
	x[0] = (-k[1] + sqrt(disc)) / (2 * k[0]);
	x[1] = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

double			sphere_intersection(t_vector origin, t_vector direction, t_figures *lst)
{
	double		closest;
	double		x[2];
	t_vector	inter_vector1;
	t_vector	inter_vector2;

	closest = INFINITY;
	solve_sphere(x, origin, direction, lst);
	if (x[0] > EPSILON && x[0] < INFINITY)
		closest = x[0];
	if (x[1] > EPSILON && x[1] < INFINITY)
		closest = x[1] < x[0] ? x[1] : closest;
	if (lst->texture != 4)
		return (closest);
	inter_vector1 = vector_add(origin, vector_scalar(x[0], direction));
	inter_vector2 = vector_add(origin, vector_scalar(x[1], direction));
	if (inter_vector1.y >= lst->figure.sphere.center.y && inter_vector2.y >= lst->figure.sphere.center.y)
		return (x[0] < x[1] ? x[0] : x[1]);
	else if (inter_vector1.y >= lst->figure.sphere.center.y)
		return (x[0]);
	else if (inter_vector2.y >= lst->figure.sphere.center.y)
		return (x[1]);
	return (INFINITY);
}
