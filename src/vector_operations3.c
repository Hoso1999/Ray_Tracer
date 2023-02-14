/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:44:32 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 19:37:56 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double		vector_distance(t_vector v1, t_vector v2)
{
	double d;

	d = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
	return (d);
}

t_vector		vector_rotx(t_vector vec, double angle)
{
	t_vector	row[3];
	t_vector	rotated_vector;
	double		radian;

	radian = angle * M_PI / 180;
	row[0] = (t_vector){1, 0, 0};
	row[1] = (t_vector){0, cos(radian), -sin(radian)};
	row[2] = (t_vector){0, sin(radian), cos(radian)};
	rotated_vector.x = vec.x * row[0].x + vec.y * row[0].y + vec.z * row[0].z;
	rotated_vector.y = vec.x * row[1].x + vec.y * row[1].y + vec.z * row[1].z;
	rotated_vector.z = vec.x * row[2].x + vec.y * row[2].y + vec.z * row[2].z;
	return (rotated_vector);
}

t_vector		vector_roty(t_vector vec, double angle)
{
	t_vector	row[3];
	t_vector	rotated_vector;
	double		radian;

	radian = angle * M_PI / 180;
	row[0] = (t_vector){cos(radian), 0, sin(radian)};
	row[1] = (t_vector){0, 1, 0};
	row[2] = (t_vector){-sin(radian), 0, cos(radian)};
	rotated_vector.x = vec.x * row[0].x + vec.y * row[0].y + vec.z * row[0].z;
	rotated_vector.y = vec.x * row[1].x + vec.y * row[1].y + vec.z * row[1].z;
	rotated_vector.z = vec.x * row[2].x + vec.y * row[2].y + vec.z * row[2].z;
	return (rotated_vector);
}

t_vector		vector_rotz(t_vector vec, double angle)
{
	t_vector	row[3];
	t_vector	rotated_vector;
	double		radian;

	radian = angle * M_PI / 180;
	row[0] = (t_vector){cos(radian), -sin(radian), 0};
	row[1] = (t_vector){sin(radian), cos(radian), 0};
	row[2] = (t_vector){0, 0, 1};
	rotated_vector.x = vec.x * row[0].x + vec.y * row[0].y + vec.z * row[0].z;
	rotated_vector.y = vec.x * row[1].x + vec.y * row[1].y + vec.z * row[1].z;
	rotated_vector.z = vec.x * row[2].x + vec.y * row[2].y + vec.z * row[2].z;
	return (rotated_vector);
}
