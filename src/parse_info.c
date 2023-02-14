/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:52:59 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:39:59 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_res(t_scene *data, char **str)
{
	if (data->resolution_init > 0)
		scene_error("Resolution (R) can only be declared once in the scene\n");
	else
		data->resolution_init = 1;
	next(str);
	data->resolution_x = file_atoi(str);
	in_range(data->resolution_x, 1, INFINITY, "resolution");
	data->resolution_y = file_atoi(str);
	in_range(data->resolution_y, 1, INFINITY, "resolution");
}

void		parse_ambient_light(t_scene *data, char **str)
{
	if (data->ambient_light_init > 0)
		scene_error(
			"Ambient lightning (A) can only be declared once in the scene\n");
	else
		data->ambient_light_init = 1;
	next(str);
	data->ambient_light_braight = file_atof(str);
	in_range(data->ambient_light_braight, 0, 1, "ambient lightning");
	data->ambient_light_color = parse_color(str);
}

void		parse_camera(t_minirt *minirt, t_scene *scene, char **str)
{
	t_camera	*elem;
	t_camera	*begin;
	int			prev_idx;

	prev_idx = 0;
	begin = minirt->current_camera;
	elem = ec_malloc(sizeof(t_camera));
	elem->next = NULL;
	if (minirt->current_camera)
	{
		while (minirt->current_camera->next)
			minirt->current_camera = minirt->current_camera->next;
		prev_idx = minirt->current_camera->index;
		minirt->current_camera->next = elem;
	}
	else
		minirt->current_camera = elem;
	next(str);
	elem->index = prev_idx + 1;
	scene->camera_number = elem->index;
	elem->origin = parse_vector(str);
	elem->normal_vector = vector_normalize(parse_vector(str));
	elem->fov = file_atoi(str);
	in_range(elem->fov, 0, 180, "camera");
	minirt->current_camera = begin ? begin : elem;
}

void		parse_light(t_scene **scene, char **str)
{
	t_light	*elem;
	t_light	*list;
	t_light *begin;

	begin = (*scene)->lights;
	list = (*scene)->lights;
	elem = ec_malloc(sizeof(t_light));
	elem->next = NULL;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elem;
		list = list->next;
	}
	else
		list = elem;
	next(str);
	list->origin = parse_vector(str);
	list->braight = file_atof(str);
	in_range(list->braight, 0, 1, "light");
	list->color = parse_color(str);
	(*scene)->lights = begin ? begin : list;
}
