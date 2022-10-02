/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concerning_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:06:14 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:58:28 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_coeficient(double (*rgb)[3], double coef, int color)
{
	unsigned int	mask;

	mask = 255 << 16;
	(*rgb)[0] += coef * ((color & mask) >> 16) / 255;
	mask >>= 8;
	(*rgb)[1] += coef * ((color & mask) >> 8) / 255;
	mask >>= 8;
	(*rgb)[2] += coef * (color & mask) / 255;
}

double	calc_specular(t_ray ray, t_intersection *inter, t_scene data, t_figures *lst)
{
	double		light;
	t_vector	direction;
	t_vector	p_to_cam;
	t_vector	reflected;

	direction = vector_substract(data.lights->origin, inter->position);
	p_to_cam = vector_substract(ray.origin, inter->position);
	reflected = reflect_ray(direction, inter->normal_vector);
	if (vector_dot(reflected, p_to_cam) > 0)
		light = data.lights->braight * pow(vector_cos(reflected, p_to_cam), lst->specular);
	else
		light = 0;
	return (light);
}

void	compute_light(t_ray ray, t_intersection *inter, t_scene data, t_figures *lst)
{
	double			light;
	double			rgb[3];
	t_vector		direction;

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	add_coeficient(&rgb, data.ambient_light_braight, data.ambient_light_color);
	while (data.lights)
	{
		direction = vector_substract(data.lights->origin, inter->position);
		(void)lst;
		if (is_lit(inter->position, direction, lst)
				&& vector_dot(inter->normal_vector, direction) > 0)
		{
			light = data.lights->braight * vector_cos(inter->normal_vector, direction);
			add_coeficient(&rgb, light, data.lights->color);
		}
		if (lst->specular)
		{
			light = calc_specular(ray, inter, data, lst);
			add_coeficient(&rgb, light, data.lights->color);
		}
		data.lights = data.lights->next;
	}
	inter->color = color_light(inter->color, rgb);
}

void	calc_normal(t_vector position, t_vector direction, t_vector *normal, t_figures *light)
{
	if (light->type == SPHERE)
	{
		*normal = vector_normalize(vector_substract(position, light->figure.sphere.center));
		if (vector_cos(direction, *normal) > 0)
		{
			*normal = vector_scalar(-1, *normal);
			light->figure.sphere.inside = 1;
		}
		else
			light->figure.sphere.inside = 0;
	}
	else
		*normal = vector_cos(direction, light->normal_vector) > 0 ? vector_scalar(-1, light->normal_vector)
											: light->normal_vector;
}

int		is_lit(t_vector origin, t_vector direction, t_figures *lst)
{
	double			in;

	while (lst)
	{
		if (lst->type == SPHERE)
			in = sphere_intersection(origin, direction, lst);
		else if (lst->type == PLANE)
			in = plane_intersection(origin, direction, lst);
		else if (lst->type == TRIANGLE)
			in = triangle_intersection(origin, direction, lst);
		else if (lst->type == SQUERE)
			in = square_intersection(origin, direction, lst);
		else if (lst->type == CYLINDER)
			in = cylinder_intersection(origin, direction, lst);
		else if (lst->type == CUBE)
			in = cube_intersection(origin, direction, lst);
		else if (lst->type == PYRAMID)
			in = pyramid_intersection(origin, direction, lst);
		if (in > EPSILON && in < 1)
			return (0);
		lst = lst->next;
	}
	return (1);
}
