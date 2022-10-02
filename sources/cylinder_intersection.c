/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:30:06 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 20:50:40 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		solve_cylinder(double x[2], t_vector origin, t_vector direction, t_figures *lst)
{
	t_vector	v;
	t_vector	u;
	double		a;
	double		b;
	double		c;

	v = vector_scalar(vector_dot(direction, lst->figure.cylinder.normal_vector), lst->figure.cylinder.normal_vector);
	v = vector_substract(direction, v);
	u = vector_scalar(vector_dot(vector_substract(origin, lst->figure.cylinder.center), lst->figure.cylinder.normal_vector),
													lst->figure.cylinder.normal_vector);
	u = vector_substract(vector_substract(origin, lst->figure.cylinder.center), u);
	a = vector_dot(v, v);
	b = 2 * vector_dot(v, u);
	c = vector_dot(u, u) - pow(lst->figure.cylinder.radius, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

static t_vector		calc_cy_normal(double x2[2], t_vector origin, t_vector direction, t_figures *lst)
{
	double	dist;
	double	x;

	if ((lst->figure.cylinder.dist1 >= 0 && lst->figure.cylinder.dist1 <= lst->figure.cylinder.height
				&& x2[0] > EPSILON) && (lst->figure.cylinder.dist2 >= 0
				&& lst->figure.cylinder.dist2 <= lst->figure.cylinder.height && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? lst->figure.cylinder.dist1 : lst->figure.cylinder.dist2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (lst->figure.cylinder.dist1 >= 0 && lst->figure.cylinder.dist1 <= lst->figure.cylinder.height
														&& x2[0] > EPSILON)
	{
		dist = lst->figure.cylinder.dist1;
		x = x2[0];
	}
	else
	{
		dist = lst->figure.cylinder.dist2;
		x = x2[1];
	}
	x2[0] = x;
	return (vector_normalize(vector_substract(vector_substract(vector_scalar(x, direction),
			vector_scalar(dist, lst->figure.cylinder.normal_vector)), vector_substract(lst->figure.cylinder.center, origin))));
}

static double	cy_intersection(t_vector origin, t_vector direction, t_vector *normal, t_figures *lst)
{
	double	x2[2];

	if (solve_cylinder(x2, origin, direction, lst) == 0)
		return (INFINITY);
	lst->figure.cylinder.dist1 = vector_dot(lst->figure.cylinder.normal_vector, vector_substract(vector_scalar(x2[0], direction),
												vector_substract(lst->figure.cylinder.center, origin)));
	lst->figure.cylinder.dist2 = vector_dot(lst->figure.cylinder.normal_vector, vector_substract(vector_scalar(x2[1], direction),
												vector_substract(lst->figure.cylinder.center, origin)));
	if (!((lst->figure.cylinder.dist1 >= 0 && lst->figure.cylinder.dist1 <= lst->figure.cylinder.height
					&& x2[0] > EPSILON) || (lst->figure.cylinder.dist2 >= 0
					&& lst->figure.cylinder.dist2 <= lst->figure.cylinder.height && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = calc_cy_normal(x2, origin, direction, lst);
	return (x2[0]);
}

static double	caps_intersection(t_vector origin, t_vector direction, t_figures *lst)
{
	double		inter_direction1;
	double		inter_direction2;
	t_vector	inter_vector1;
	t_vector	inter_vector2;
	t_vector	center;

	center = vector_add(lst->figure.cylinder.center, vector_scalar(lst->figure.cylinder.height, lst->figure.cylinder.normal_vector));
	inter_direction1 = solve_plane(origin, direction, lst->figure.cylinder.center, lst->figure.cylinder.normal_vector);
	inter_direction2 = solve_plane(origin, direction, center, lst->figure.cylinder.normal_vector);
	if (inter_direction1 < INFINITY || inter_direction2 < INFINITY)
	{
		inter_vector1 = vector_add(origin, vector_scalar(inter_direction1, direction));
		inter_vector2 = vector_add(origin, vector_scalar(inter_direction2, direction));
		if ((inter_direction1 < INFINITY && vector_distance(inter_vector1, lst->figure.cylinder.center) <= lst->figure.cylinder.radius)
				&& (inter_direction2 < INFINITY && vector_distance(inter_vector2, center) <= lst->figure.cylinder.radius))
			return (inter_direction1 < inter_direction2 ? inter_direction1 : inter_direction2);
		else if (inter_direction1 < INFINITY
						&& vector_distance(inter_vector1, lst->figure.cylinder.center) <= lst->figure.cylinder.radius)
			return (inter_direction1);
		else if (inter_direction2 < INFINITY && vector_distance(inter_vector2, center) <= lst->figure.cylinder.radius)
			return (inter_direction2);
		return (INFINITY);
	}
	return (INFINITY);
}

double			cylinder_intersection(t_vector origin, t_vector direction, t_figures *lst)
{
	double		cylinder_inter;
	double		caps_inter;
	t_vector	cy_normal;

	cylinder_inter = cy_intersection(origin, direction, &cy_normal, lst);
	if (lst->texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = caps_intersection(origin, direction, lst);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			lst->normal_vector = cy_normal;
			return (cylinder_inter);
		}
		lst->normal_vector = lst->figure.cylinder.normal_vector;
		return (caps_inter);
	}
	return (INFINITY);
}
