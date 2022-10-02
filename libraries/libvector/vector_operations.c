/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:29:36 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 19:28:45 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_define(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector		vector_add(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

t_vector		vector_substract(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

double		vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector		vector_cross(t_vector a, t_vector b)
{
	t_vector	cross_vec;

	cross_vec.x = a.y * b.z - a.z * b.y;
	cross_vec.y = a.z * b.x - a.x * b.z;
	cross_vec.z = a.x * b.y - a.y * b.x;
	return (cross_vec);
}
