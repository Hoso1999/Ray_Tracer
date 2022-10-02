/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:29:34 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 19:25:04 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

t_vector		vector_define(double x, double y, double z);

t_vector		vector_add(t_vector a, t_vector b);

t_vector		vector_substract(t_vector a, t_vector b);

t_vector		vector_product(t_vector a, t_vector b);

double			vector_dot(t_vector a, t_vector b);

t_vector		vector_cross(t_vector a, t_vector b);

double			vector_mod(t_vector v);

t_vector		vector_normalize(t_vector v);

double			vector_sin(t_vector a, t_vector b);

double			vector_cos(t_vector a, t_vector b);

t_vector		vector_scalar(double n, t_vector v);

double			vector_distance(t_vector v1, t_vector v2);

t_vector		vector_rotx(t_vector vec, double angle);

t_vector		vector_roty(t_vector vec, double angle);

t_vector		vector_rotz(t_vector vec, double angle);

#endif
