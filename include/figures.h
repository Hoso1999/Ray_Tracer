/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:48:18 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 19:48:37 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "minirt.h"

typedef struct	s_sphere
{
	t_vector	center;
	double		radius;
	int			inside;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	position;
}				t_plane;

typedef struct	s_square
{
	t_vector	center;
	double		side;

}				t_square;

typedef struct	s_cylinder
{
	t_vector	center;
	t_vector	normal_vector;
	double		radius;
	double		height;
	double		dist1;
	double		dist2;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector	first;
	t_vector	second;
	t_vector	third;
}				t_triangle;

#endif
