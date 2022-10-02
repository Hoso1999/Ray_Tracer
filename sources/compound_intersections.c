/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:30:28 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 20:28:35 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		init_cube(t_cube *cube, t_figures *lst)
{
	cube->normal_vectors[0] = (t_vector) {1, 0, 0};
	cube->normal_vectors[1] = (t_vector) {-1, 0, 0};
	cube->normal_vectors[2] = (t_vector) {0, 1, 0};
	cube->normal_vectors[3] = (t_vector) {0, -1, 0};
	cube->normal_vectors[4] = (t_vector) {0, 0, 1};
	cube->normal_vectors[5] = (t_vector) {0, 0, -1};
	cube->center = lst->figure.squere.center;
	cube->squere.figure.squere.side = lst->figure.squere.side;
}

double			cube_intersection(t_vector origin, t_vector direction, t_figures *lst)
{
	t_cube		cube;
	t_vector	cl_normal;
	double		cl_inter;
	double		inter;
	int			i;

	init_cube(&cube, lst);
	cl_inter = INFINITY;
	i = 0;
	while (i < 6)
	{
		cube.squere.figure.squere.center = vector_add(cube.center,
							vector_scalar(lst->figure.squere.side / 2, cube.normal_vectors[i]));
		cube.squere.normal_vector = cube.normal_vectors[i];
		inter = square_intersection(origin, direction, &(cube.squere));
		if (inter > EPSILON && inter < cl_inter)
		{
			cl_inter = inter;
			cl_normal = cube.squere.normal_vector;
		}
		i++;
	}
	lst->normal_vector = cl_normal;
	return (cl_inter);
}

static void		init_pyramid(t_pyramid *pyramid, t_figures *lst)
{
	int	i;

	pyramid->normal_vectors[0] = (t_vector) {1, 0, 0};
	pyramid->normal_vectors[1] = (t_vector) {0, 0, 1};
	pyramid->normal_vectors[2] = (t_vector) {-1, 0, 0};
	pyramid->normal_vectors[3] = (t_vector) {0, 0, -1};
	pyramid->normal_vectors[4] = (t_vector) {1, 0, 0};
	pyramid->triangle_center = vector_add(lst->figure.squere.center,
					vector_scalar(lst->figure.squere.side, (t_vector){0, 1, 0}));
	pyramid->squere.figure.squere.side = lst->figure.squere.side;
	pyramid->squere.figure.squere.center = lst->figure.squere.center;
	pyramid->squere.normal_vector = (t_vector) {0, -1, 0};
	i = 0;
	while (i < 4)
	{
		pyramid->corners[i] = vector_add(lst->figure.squere.center,
						vector_scalar(lst->figure.squere.side / 2, pyramid->normal_vectors[i]));
		pyramid->corners[i] = vector_add(pyramid->corners[i],
						vector_scalar(lst->figure.squere.side / 2, pyramid->normal_vectors[i + 1]));
		i++;
	}
	pyramid->triangle.figure.triangle.third = pyramid->triangle_center;
}

double			pyramid_intersection(t_vector origin, t_vector direction, t_figures *lst)
{
	t_pyramid		pyramid;
	t_vector		cl_normal;
	double			cl_inter;
	double			inter;
	int				i;

	init_pyramid(&pyramid, lst);
	cl_inter = INFINITY;
	i = 0;
	while (i < 4)
	{
		pyramid.triangle.figure.triangle.first = pyramid.corners[i];
		pyramid.triangle.figure.triangle.second = i < 3 ? pyramid.corners[i + 1] : pyramid.corners[0];
		pyramid.triangle.normal_vector = vector_cross(vector_substract(pyramid.triangle.figure.triangle.third, pyramid.triangle.figure.triangle.first),
							vector_substract(pyramid.triangle.figure.triangle.second, pyramid.triangle.figure.triangle.first));
		inter = triangle_intersection(origin, direction, &(pyramid.triangle));
		if (inter > EPSILON && inter < cl_inter)
		{
			cl_inter = inter;
			cl_normal = pyramid.triangle.normal_vector;
		}
		i++;
	}
	lst->normal_vector = cl_normal;
	return (cl_inter);
}
