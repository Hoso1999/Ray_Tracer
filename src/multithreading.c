/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 18:17:55 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 20:52:55 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		*render_thread(void *ptr)
{
	t_wrapper	*w;

	w = (t_wrapper *)ptr;
	while (w->minirt.current_camera)
	{
		render_scene(w);
		w->minirt.current_camera = w->minirt.current_camera->next;
	}
	return (NULL);
}

void			multithreaded_render(t_wrapper wrapper[NUM_THREADS])
{
	pthread_t	threads[NUM_THREADS];
	int			i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_create(&threads[i], NULL, render_thread, &wrapper[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(threads[i++], NULL);
}

void			wrapp_data(t_minirt minirt, t_scene scene, t_figures *lst,
														t_wrapper *wrapper)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		wrapper[i].minirt = minirt;
		wrapper[i].scene = scene;
		wrapper[i].lst = lst;
		wrapper[i].thread_id = i;
		i++;
	}
}
