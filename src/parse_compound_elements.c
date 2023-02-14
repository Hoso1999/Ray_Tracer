/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compound_elements.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:30:57 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:40:24 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_cube(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = CUBE;
	next(str);
	lst->figure.squere.center = parse_vector(str);
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

void		parse_pyramid(t_figures **elem, char **str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->type = PYRAMID;
	next(str);
	lst->figure.squere.center = parse_vector(str);
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
