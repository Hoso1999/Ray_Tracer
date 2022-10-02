/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:06:59 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/04/04 20:08:20 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

int			next_cam(int keycode, t_wrapper *wrap)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == SP_KEY)
	{
		wrap->minirt.current_camera = (wrap->minirt.current_camera->next) ? wrap->minirt.current_camera->next : wrap->minirt.camera_begin;
		mlx_put_image_to_window(
					wrap->minirt.mlx, wrap->minirt.win, wrap->minirt.current_camera->ptr_img, 0, 0);
	}
	return (1);
}

void		init_mlx(t_minirt *minirt, t_scene *data)
{
	t_camera	*cam_begin;
	int			x_displayres;
	int			y_displayres;

	minirt->mlx = mlx_init();
	if (OS_NAME == 2)
	{
		mlx_get_screen_size(minirt->mlx, &x_displayres, &y_displayres);
		data->resolution_x = data->resolution_x < x_displayres ? data->resolution_x : x_displayres;
		data->resolution_y = data->resolution_y < y_displayres ? data->resolution_y : y_displayres;
	}
	cam_begin = minirt->current_camera;
	minirt->camera_begin = minirt->current_camera;
	while (minirt->current_camera)
	{
		minirt->current_camera->ptr_img = mlx_new_image(minirt->mlx, data->resolution_x, data->resolution_y);
		minirt->current_camera->img_px = (int *)mlx_get_data_addr(minirt->current_camera->ptr_img,
			&minirt->current_camera->bits_per_pixel, &minirt->current_camera->size_line, &minirt->current_camera->endian);
		minirt->current_camera = minirt->current_camera->next;
	}
	minirt->current_camera = cam_begin;
}

void		success_message(int ac)
{
	int		t;

	t = NUM_THREADS;
	if (ac == 2)
	{
		if (NUM_THREADS == 1)
			printf("\nScene successfully rendered with 1 thread, ");
		else
			printf("\nScene successfully rendered with %d threads, ", t);
		printf("press ESC at any momnet to close the program.\n");
		printf("If the scene has several cameras, ");
		printf("press space to change between them\n\n");
	}
	else
	{
		printf("\nScene successfully saved to BMP\n");
		printf("The file has been saved into the \"images\" directory\n\n");
		exit(EXIT_SUCCESS);
	}
}

void		graphic_loop(t_minirt minirt, t_scene scene, t_figures *lst)
{
	t_wrapper wrap[NUM_THREADS];
	wrapp_data(minirt, scene, lst, wrap);
	int i = 0;
	while(i < NUM_THREADS)
	{
		wrap[i].minirt.win = mlx_new_window(wrap[i].minirt.mlx, scene.resolution_x, scene.resolution_y,
																"miniRT");
		mlx_put_image_to_window(wrap[i].minirt.mlx, wrap[i].minirt.win, wrap[i].minirt.current_camera->ptr_img, 0, 0);
		mlx_hook(wrap[i].minirt.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_program, 0);
		mlx_hook(wrap[i].minirt.win, KEYPRESS, KEYPRESSMASK, next_cam, &wrap[i]);
		mlx_loop(wrap[i].minirt.mlx);

	}
	
}
