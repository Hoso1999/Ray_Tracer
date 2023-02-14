/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:49:05 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:18:12 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_sphere(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = SPHERE;
	next(str);
	lst->figure.sphere.center = parse_vector(str);
	lst->figure.sphere.radius = file_atof(str) / 2;
	in_range(lst->figure.sphere.radius, 0, INFINITY, "sphere");
	lst->specular = file_atoi(str);
	in_range(lst->specular, 0, INFINITY, "sphere");
	lst->reflective_index = file_atof(str);
	in_range(lst->reflective_index, 0, 1, "sphere");
	lst->refrective_index = file_atof(str);
	in_range(lst->refrective_index, 0, INFINITY, "sphere");
	lst->texture = file_atoi(str);
	in_range(lst->texture, 0, 5, "sphere");
	if (lst->texture == 2)
		lst->wave_length = file_atof(str);
	lst->color = parse_color(str);
}

void		parse_plane(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = PLANE;
	next(str);
	lst->figure.plane.position = parse_vector(str);
	lst->normal_vector = vector_normalize(parse_vector(str));
	lst->specular = file_atoi(str);
	in_range(lst->specular, 0, INFINITY, "plane");
	lst->reflective_index = file_atof(str);
	in_range(lst->reflective_index, 0, 1, "plane");
	lst->refrective_index = file_atof(str);
	in_range(lst->refrective_index, 0, INFINITY, "plane");
	lst->texture = file_atoi(str);
	in_range(lst->texture, 0, 5, "plane");
	if (lst->texture == 2)
		lst->wave_length = file_atof(str);
	lst->color = parse_color(str);
}

void		parse_square(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = SQUERE;
	next(str);
	lst->figure.squere.center = parse_vector(str);
	lst->normal_vector = vector_normalize(parse_vector(str));
	lst->figure.squere.side = file_atof(str);
	in_range(lst->figure.squere.side, 0, INFINITY, "square");
	lst->specular = file_atoi(str);
	in_range(lst->specular, 0, INFINITY, "square");
	lst->reflective_index = file_atof(str);
	in_range(lst->reflective_index, 0, 1, "square");
	lst->refrective_index = file_atof(str);
	in_range(lst->refrective_index, 0, INFINITY, "square");
	lst->texture = file_atoi(str);
	in_range(lst->texture, 0, 5, "square");
	if (lst->texture == 2)
		lst->wave_length = file_atof(str);
	lst->color = parse_color(str);
}

void		parse_triangle(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = TRIANGLE;
	next(str);
	lst->figure.triangle.first = parse_vector(str);
	lst->figure.triangle.second = parse_vector(str);
	lst->figure.triangle.third = parse_vector(str);
	lst->normal_vector = vector_cross(vector_substract(lst->figure.triangle.third, lst->figure.triangle.first),
			vector_substract(lst->figure.triangle.second, lst->figure.triangle.first));
	lst->specular = file_atoi(str);
	in_range(lst->specular, 0, INFINITY, "triangle");
	next(str);
	lst->reflective_index = file_atof(str);
	in_range(lst->reflective_index, 0, 1, "triangle");
	lst->refrective_index = file_atof(str);
	in_range(lst->refrective_index, 0, INFINITY, "triangle");
	lst->texture = file_atoi(str);
	in_range(lst->texture, 0, 5, "triangle");
	if (lst->texture == 2)
		lst->wave_length = file_atof(str);
	lst->color = parse_color(str);
}

void		parse_cylinder(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = CYLINDER;
	next(str);
	lst->figure.cylinder.center = parse_vector(str);
	lst->figure.cylinder.normal_vector = vector_normalize(parse_vector(str));
	lst->figure.cylinder.radius = file_atof(str) / 2;
	in_range(lst->figure.cylinder.radius, 0, INFINITY, "cylinder");
	lst->figure.cylinder.height = file_atof(str);
	in_range(lst->figure.cylinder.height, 0, INFINITY, "cylinder");
	lst->specular = file_atoi(str);
	in_range(lst->specular, 0, INFINITY, "cylinder");
	lst->reflective_index = file_atof(str);
	in_range(lst->reflective_index, 0, 1, "cylinder");
	lst->refrective_index = file_atof(str);
	in_range(lst->refrective_index, 0, INFINITY, "cylinder");
	lst->texture = file_atoi(str);
	in_range(lst->texture, 0, 5, "cylinder");
	if (lst->texture == 2)
		lst->wave_length = file_atof(str);
	lst->color = parse_color(str);
}
