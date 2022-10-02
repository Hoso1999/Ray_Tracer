/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:31:29 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:10:48 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		parse2(t_figures **lst, char *str)
{
	if (*str == 'p' && *(str + 1) == 'y' && *(str++) && *(str++))
		parse_pyramid(lst, &str);
	else if (*str == 't' && *(str + 1) == 'r' && *(str++) && *(str++))
		parse_triangle(lst, &str);
}

static void		parse(t_minirt *minirt, t_scene *scene, t_figures **lst,
																char **strptr)
{
	char *str;

	str = *strptr;
	if (*str == 'R' && *(str++))
		parse_res(scene, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(scene, &str);
	else if (*str == 'c' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(minirt, scene, &str);
	else if (*str == 'c' && *(str + 1) == 'y' && *(str++) && *(str++))
		parse_cylinder(lst, &str);
	else if (*str == 'c' && *(str + 1) == 'u' && *(str++) && *(str++))
		parse_cube(lst, &str);
	else if (*str == 'l' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_light(&scene, &str);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str++))
		parse_sphere(lst, &str);
	else if (*str == 's' && *(str + 1) == 'q' && *(str++) && *(str++))
		parse_square(lst, &str);
	else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str++))
		parse_plane(lst, &str);
	parse2(lst, str);
	*strptr = str;
}

static void		parse_elems(t_minirt *minirt, t_scene *scene, t_figures **lst,
																	char *str)
{
	scene->resolution_init = 0;
	scene->ambient_light_init = 0;
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
		}
		else
			parse(minirt, scene, lst, &str);
		str++;
	}
	if (scene->resolution_init == 0 || scene->ambient_light_init == 0 || minirt->current_camera == NULL)
		scene_error("Not enough elements to render a scene\n");
}

void			parse_scene(t_minirt *minirt, t_scene *scene, t_figures **lst,
																	char **av)
{
	char		*str;
	int			fd;

	*lst = NULL;
	scene->lights = NULL;
	minirt->current_camera = NULL;
	write(1, "Parsing scene...\n", 17);
	str = (char *)ec_malloc(sizeof(char) * (BUFSIZE + 1));
	if ((fd = open(av[1], 0)) == -1)
		fatal("while opening file");
	str = readfile(str, fd);
	parse_elems(minirt, scene, lst, str);
	free(str);
}
