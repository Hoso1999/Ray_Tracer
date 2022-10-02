/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:46:49 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 19:31:59 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double		vector_mod(t_vector v)
{
	return (sqrt(vector_dot(v, v)));
}

t_vector		vector_normalize(t_vector v)
{
	t_vector	normalized_vector;
	double	mod;

	mod = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalized_vector.x = v.x / mod;
	normalized_vector.y = v.y / mod;
	normalized_vector.z = v.z / mod;
	return (normalized_vector);
}

double		vector_sin(t_vector a, t_vector b)
{
	return (sqrt(1 - pow(vector_cos(a, b), 2)));
}

double		vector_cos(t_vector a, t_vector b)
{
	return (vector_dot(a, b) / (vector_mod(a) * vector_mod(b)));
}

t_vector		vector_scalar(double n, t_vector v)
{
	t_vector	vector;

	vector.x = n * v.x;
	vector.y = n * v.y;
	vector.z = n * v.z;
	return (vector);
}
