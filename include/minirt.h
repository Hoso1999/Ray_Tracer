/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:42:41 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 22:25:41 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "mlx_defines.h"
# include "libft.h"
# include "vector.h"
# include "figures.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# ifdef MACOS
#  define OS_NAME			1
# endif

# ifdef LINUX
#  define OS_NAME			2
# endif

# define BUFSIZE			32

# ifndef NUM_THREADS
#  define NUM_THREADS		4
# endif

# define REFLECTION_LIMIT	3

# define EPSILON			0.00001

typedef enum				e_type_shapes
{
							SPHERE,
							PLANE,
							SQUERE,
							TRIANGLE,
							CYLINDER,
							CUBE,
							PYRAMID,
							NONE
}							t_type_shapes;

typedef struct				s_ray
{
	t_vector				origin;
	t_vector				direction;
}							t_ray;

typedef union				u_shapes
{
	t_sphere				sphere;
	t_plane					plane;
	t_square				squere;
	t_cylinder				cylinder;
	t_triangle				triangle;
}							t_shapes;

typedef struct				s_camera
{
	int						init;
	int						index;
	t_vector				origin;
	t_vector				normal_vector;
	int						fov;
	void					*ptr_img;
	int						*img_px;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
	struct s_camera			*next;
}							t_camera;

typedef struct				s_light
{
	t_vector				origin;
	double					braight;
	int						color;
	struct s_light			*next;
}							t_light;

typedef struct				s_scene
{
	int						resolution_init;
	int						resolution_x;
	int						resolution_y;
	int						camera_number;
	t_light					*lights;
	int						ambient_light_init;
	double					ambient_light_braight;
	int						ambient_light_color;
	int						background;
}							t_scene;

typedef struct				s_figures
{
	t_type_shapes			type;
	t_shapes				figure;
	int						color;
	int						specular;
	double					reflective_index;
	double					refrective_index;
	int						texture;
	t_vector				normal_vector;
	double					wave_length;
	struct s_figures		*next;
}					 		t_figures;

typedef struct				s_minirt
{
	void					*mlx;
	void					*win;
	t_camera				*current_camera;
	t_camera				*camera_begin;
}							t_minirt;

typedef struct				s_wrapper
{
	t_minirt				minirt;
	t_scene					scene;
	t_figures				*lst;
	int						thread_id;
	int						thread_i;
	int						thread_j;
}							t_wrapper;

typedef struct				s_rss
{
	int						limit;
	int						resolution_x;
	int						resolution_y;
	int						i;
	int						j;
}							t_rss;

typedef struct				s_intersection
{
	int						color;
	int						ref_color;
	t_vector				normal_vector;
	t_vector				position;
	t_vector				ref_vec;
}							t_intersection;

typedef struct				s_bmp_header
{
	char					type[2];
	unsigned int			size;
	unsigned int			reserved;
	unsigned int			offset;
}							t_bmphead;

typedef struct				s_dib_header
{
	unsigned int			size;
	int						width;
	int						height;
	unsigned short			colplanes;
	unsigned short			bits_per_pixel;
	unsigned int			compression;
	unsigned int			img_size;
	int						x_ppm;
	int						y_ppm;
	unsigned int			color_number;
	unsigned int			important_color;
}							t_dibhead;

typedef struct				s_thread
{
	pthread_t				threads[NUM_THREADS];
	t_wrapper				wrapper[NUM_THREADS];
	int						i;
}							t_thread;

typedef struct				s_create_squere
{
	t_vector				half_size;
	t_vector				floor;
	t_vector				center_to_ip;
}							t_create_squere;

typedef struct				s_cube
{
	t_figures				squere;
	t_vector				center;
	t_vector				normal_vectors[6];
}							t_cube;

typedef struct				s_pyramid
{
	t_figures				squere;
	t_figures				triangle;
	t_vector				triangle_center;
	t_vector				normal_vectors[5];
	t_vector				corners[4];
}							t_pyramid;

/*
**			 	Parsing functions
*/

void						parse_scene(t_minirt *mlx, t_scene *data, t_figures **lst,
																	char **av);

void						parse_res(t_scene *data, char **str);

void						parse_ambient_light(t_scene *data, char **str);

void						parse_camera(t_minirt *mlx, t_scene *data, char **str);

void						parse_light(t_scene **data, char **str);

void						parse_sphere(t_figures **elem, char **str);

void						parse_plane(t_figures **elem, char **str);

void						parse_square(t_figures **elem, char **str);

void						parse_triangle(t_figures **elem, char **str);

void						parse_cylinder(t_figures **elem, char **str);

void						parse_cube(t_figures **elem, char **str);

void						parse_pyramid(t_figures **elem, char **str);

/*
**				Parsing help functions
*/

char						*readfile(char *str, int fd);

int							file_atoi(char **str);

double						file_atof(char **str);

void						in_range(double nb, double min, double max, char *function);

void						next(char **str);

void						comma(char **str);

t_vector					parse_vector(char **str);

int							parse_color(char **str);

void						ft_addnewlst_back(t_figures **alst);

/*
**				Intersection functions
*/
double						sphere_intersection(t_vector o, t_vector d, t_figures *lst);

double						plane_intersection(t_vector o, t_vector d, t_figures *lst);

double						square_intersection(t_vector o, t_vector d, t_figures *lst);

double						triangle_intersection(t_vector o, t_vector d, t_figures *lst);

double						cylinder_intersection(t_vector o, t_vector d, t_figures *lst);

double						cube_intersection(t_vector o, t_vector d, t_figures *lst);

double						pyramid_intersection(t_vector o, t_vector d, t_figures *lst);

/*
**				Intersections help functions
*/

void						try_all_intersections(t_ray ray, t_figures *lst,
											t_figures *clfig, double *clint);

double						solve_plane(t_vector o, t_vector d, t_vector plane_p,
														t_vector plane_nv);

/*
**				Ray tracing
*/

void						render_scene(t_wrapper *w);

int							trace_ray(t_vector o, t_vector d, t_wrapper *w, int depth);

int							calc_ray(int n, t_rss rss, t_wrapper *w);

void						calc_normal(t_vector p, t_vector d, t_vector *normal, t_figures *lst);

int							is_lit(t_vector o, t_vector d, t_figures *lst);

void						compute_light(t_ray ray, t_intersection *inter, t_scene data,
															t_figures *lst);

/*
**				Super Sampling
*/

int							*sample_pixel(int *edge_color, int last[2], t_rss rss,
																t_wrapper *w);

int							supersample(int *color, t_rss rss, t_wrapper *w);

/*
**				Multithreaded rendering
*/

void						wrapp_data(t_minirt mlx, t_scene data, t_figures *lst,
															t_wrapper *wrapper);

void						multithreaded_render(t_wrapper wrapper[NUM_THREADS]);

/*
**				Error handling functions and success message
*/

void						*ec_malloc(unsigned int size);

void						fatal(char *message);

void						scene_error(char *message);

void						usage(char *program_name);

void						success_message(int ac);

/*
**				Minilibx functions
*/

void						init_mlx(t_minirt *mlx, t_scene *data);

void						graphic_loop(t_minirt mlx, t_scene data, t_figures *lst);

int							next_cam(int keycode, t_wrapper *wrap);

int							close_program(void *param);

/*
**				Bmp exporter
*/

void						do_the_bmp_thing(t_minirt mlx, t_scene data, char *name);

/*
**				Color Operations
*/

int							color_product(int color, double coef);

int							color_add(int color_a, int color_b);

int							color_difference(int color1, int color2);

int							color_light(int color, double rgb[3]);

int							average(int color1, int color2);

int							average_supersampled_color(int *color);

/*
**				Utils
*/

t_vector					reflect_ray(t_vector ray, t_vector normal);

void						apply_texture(int texture, t_intersection *inter, t_figures *lst);

int							rainbow(t_intersection *t_intersection);

#endif
