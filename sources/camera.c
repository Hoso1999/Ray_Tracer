/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 18:17:31 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:40:33 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector		set_scene_camera(int n, t_rss rss, t_minirt rt)
{
	double	ratio;
	double	fov;
	double	offset_x;
	double	offset_y;
	t_vector	position;

	offset_x = ((n % 3) * 0.5);
	offset_y = ((n / 3) * 0.5);
	ratio = (double)(rss.resolution_x) / (double)(rss.resolution_y);
	fov = tan((rt.current_camera->fov * M_PI / 180) / 2);
	position.x =
	((2 * ((rss.i + offset_x) / rss.resolution_x)) - 1) * ratio * fov;
	position.y = (1 - (2 * ((rss.j + offset_y) / rss.resolution_y))) * fov;
	position.x *= -1;
	position.z = 1;
	vector_normalize(position);
	return (position);
}

static t_vector		look_at(t_vector d, t_vector normal_vector)
{
	t_vector	x;
	t_vector	y;
	t_vector	z;
	t_vector	tmp;
	t_vector	rotated;

	tmp = vector_define(0, 1, 0);
	z = normal_vector;
	if (normal_vector.y == 1 || normal_vector.y == -1)
		x = normal_vector.y == 1 ? (t_vector) {1, 0, 0} : (t_vector) {-1, 0, 0};
	else
		x = vector_cross(tmp, z);
	y = vector_cross(z, x);
	rotated.x = d.x * x.x + d.y * y.x + d.z * z.x;
	rotated.y = d.x * x.y + d.y * y.y + d.z * z.y;
	rotated.z = d.x * x.z + d.y * y.z + d.z * z.z;
	return (rotated);
}

int				calc_ray(int n, t_rss rss, t_wrapper *w)
{
	t_vector	direction;
	int			color;

	direction = set_scene_camera(n, rss, w->minirt);
	direction = look_at(direction, w->minirt.current_camera->normal_vector);
	color = trace_ray(w->minirt.current_camera->origin, direction, w, REFLECTION_LIMIT);
	return (color);
}
