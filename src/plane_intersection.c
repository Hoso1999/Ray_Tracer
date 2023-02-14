/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:29:55 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:16:14 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double			solve_plane(t_vector o, t_vector d, t_vector plane_p, t_vector plane_nv)
{
	double	x;
	double	denom;

	denom = vector_dot(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (vector_dot(plane_nv, vector_substract(plane_p, o))) / denom;
	return (x > 0 ? x : INFINITY);
}

double			plane_intersection(t_vector o, t_vector d, t_figures *lst)
{
	return (solve_plane(o, d, lst->figure.plane.position, lst->normal_vector));
}

double			square_intersection(t_vector o, t_vector d, t_figures *lst)
{
	t_vector	ip;
	t_create_squere	squere;
	double	id;
	double	cos1;
	double	limit;

	id = solve_plane(o, d, lst->figure.squere.center, lst->normal_vector);
	ip = vector_add(o, vector_scalar(id, d));
	squere.floor = fabs(lst->normal_vector.y) == 1 ? vector_define(1, 0, 0) : vector_define(0, 1, 0);
	squere.half_size = vector_cross(lst->normal_vector, squere.floor);
	squere.center_to_ip = vector_substract(ip, lst->figure.squere.center);
	cos1 = fabs(vector_cos(squere.half_size, squere.center_to_ip));
	if (cos1 < sqrt(2) / 2)
		cos1 = cos(M_PI_2 - acos(cos1));
	limit = (lst->figure.squere.side / 2) / cos1;
	if (vector_mod(squere.center_to_ip) <= limit)
		return (id);
	return (INFINITY);
}

static int		p_is_outside(t_vector p1, t_vector p2, t_vector p3, t_vector ip)
{
	t_vector	v1;
	t_vector	v2;
	t_vector	vp;

	v1 = vector_substract(p2, p1);
	v2 = vector_substract(p3, p1);
	vp = vector_substract(ip, p1);
	if (vector_cos(vector_cross(v1, v2), vector_cross(v1, vp)) < 0)
		return (1);
	return (0);
}

double			triangle_intersection(t_vector o, t_vector d, t_figures *lst)
{
	double	id;
	t_vector	ip;

	id = solve_plane(o, d, lst->figure.triangle.first, lst->normal_vector);
	ip = vector_add(o, vector_scalar(id, d));
	if (p_is_outside(lst->figure.triangle.first, lst->figure.triangle.second, lst->figure.triangle.third, ip))
		return (INFINITY);
	if (p_is_outside(lst->figure.triangle.second, lst->figure.triangle.third, lst->figure.triangle.first, ip))
		return (INFINITY);
	if (p_is_outside(lst->figure.triangle.third, lst->figure.triangle.first, lst->figure.triangle.second, ip))
		return (INFINITY);
	return (id);
}
