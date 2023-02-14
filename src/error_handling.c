/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:05:30 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:57:29 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		fatal(char *message)
{
	char error_message[100];

	ft_strcpy(error_message, "[!!] Fatal Error ");
	ft_strncat(error_message, message, 83);
	perror(error_message);
	exit(EXIT_FAILURE);
}

void		scene_error(char *message)
{
	char error_message[100];

	ft_strcpy(error_message, "Scene Error: ");
	ft_strncat(error_message, message, 87);
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void		*ec_malloc(unsigned int size)
{
	void *pointer;

	pointer = malloc(size);
	if (pointer == NULL)
		fatal("in malloc() on memory allocation");
	return (pointer);
}

void		usage(char *program_name)
{
	printf("Usage: %s <scene.rt>\n", program_name);
	exit(EXIT_FAILURE);
}

#ifndef LINUX

int			mlx_get_screen_size(void *mlx, int *sizex, int *sizey)
{
	mlx = (int*)mlx;
	sizex = sizey;
	return (0);
}
#endif
