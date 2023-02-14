/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:39:55 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/06/16 17:45:58 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		refract_ray(t_vector d, t_vector normal, t_figures *lst)
{
	double	cosi;
	double	etai;
	double	etat;
	double	eta;
	double	k;

	cosi = vector_dot(d, normal);
	etai = 1;
	etat = lst->refrective_index;
	if (lst->figure.sphere.inside == 1)
	{
		k = etai;
		etai = etat;
		etat = k;
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? reflect_ray(vector_scalar(-1, d), normal)
		: vector_add(vector_scalar(eta, d), vector_scalar(eta * cosi - sqrt(k), normal)));
}

int			trace_ray(t_vector o, t_vector d, t_wrapper *w, int depth)
{
	t_ray				ray;
	t_figures			cl_fig;
	t_intersection		inter;
	double				closest_intersection;
	double				r;

	ray.origin = o;
	ray.direction = d;
	closest_intersection = INFINITY;
	cl_fig.type = NONE;
	try_all_intersections(ray, w->lst, &cl_fig, &closest_intersection);
	inter.position = vector_add(o, vector_scalar(closest_intersection, d));
	calc_normal(inter.position, d, &(inter.normal_vector), &cl_fig);
	inter.color = cl_fig.type != NONE ? cl_fig.color : w->scene.background;
	apply_texture(cl_fig.texture, &inter, w->lst);
	compute_light(ray, &inter, w->scene, w->lst);
	r = cl_fig.type != NONE ? cl_fig.reflective_index : 0;
	cl_fig.refrective_index = cl_fig.type != NONE ? cl_fig.refrective_index : 0;
	if (cl_fig.refrective_index > 0)
		inter.color = trace_ray(inter.position,
				refract_ray(d, inter.normal_vector, &cl_fig), w, depth);
	if (r > 0 && depth > 0)
		inter.ref_color = trace_ray(inter.position,
				reflect_ray(vector_scalar(-1, d), inter.normal_vector), w, depth - 1);
	return (color_add(color_product(inter.color, 1 - r),color_product(inter.ref_color, r)));
}

int			calc_pixel_color(int *edge_color, int last[2], t_wrapper *w)
{
	t_rss	rss;
	int		*color;

	rss.limit = 3;
	rss.resolution_x = w->scene.resolution_x;
	rss.resolution_y = w->scene.resolution_y;
	rss.i = w->thread_i;
	rss.j = w->thread_j;
	w->scene.background = 0x202020;
	color = sample_pixel(edge_color, last, rss, w);
	if (color_difference(color[0], color[3])
		|| color_difference(color[1], color[2]))
		return (supersample(color, rss, w));
	return (average_supersampled_color(color));
}

void		render_scene(t_wrapper *w)
{
	int		edge_color[w->scene.resolution_x + 2];
	int		last[3];
	int		color;
	int		n;

	n = w->scene.resolution_y / NUM_THREADS;
	w->thread_j = n * w->thread_id;
	while (w->thread_j < (n * (w->thread_id + 1)))
	{
		w->thread_i = 0;
		while (w->thread_i < w->scene.resolution_x)
		{
			color = calc_pixel_color(edge_color, last, w);
			w->minirt.current_camera->img_px[w->thread_j * w->scene.resolution_x + w->thread_i] = color;
			w->thread_i++;
		}
		if (w->thread_id == NUM_THREADS - 1)
			ft_printf("\rRendering scene... (cam %d/%d) [%d%%]",
			w->minirt.current_camera->index, w->scene.camera_number, 100 * (w->thread_j % n) / n);
		w->thread_j++;
	}
	if (w->thread_id == NUM_THREADS - 1)
		ft_printf("\rRendering scene... (cam %d/%d) [100%%]\n",
											w->minirt.current_camera->index, w->scene.camera_number);
}

int			main(int ac, char **av)
{
	t_wrapper	wrapper[NUM_THREADS];
	t_minirt	minirt;
	t_scene		scene;
	t_figures	*lst;

	if (ac < 2 || ac > 3)
		usage(av[0]);
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		scene_error("invalid argument\n");
	parse_scene(&minirt, &scene, &lst, av);
	init_mlx(&minirt, &scene);
	wrapp_data(minirt, scene, lst, wrapper);
	multithreaded_render(wrapper);
	if (ac == 3)
		do_the_bmp_thing(minirt, scene, av[1]);
	success_message(ac);
	graphic_loop(minirt, scene, lst);
	return (0);
}
