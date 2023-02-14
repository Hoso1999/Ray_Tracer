/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 18:18:07 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:17:40 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	checkerboard(t_intersection *inter)
{
	int			black;
	int			white;
	t_vector	coords;
	t_vector	val;
	int			party_mix;

	black = 0x000000;
	white = 0xffffff;
	coords.x = abs((int)floor(inter->position.x));
	coords.y = abs((int)floor(inter->position.y));
	coords.z = abs((int)floor(inter->position.z));
	val.x = (int)coords.x % 2;
	val.y = (int)coords.y % 2;
	val.z = (int)coords.z % 2;
	party_mix = ((int)val.x ^ (int)val.y) ^ (int)val.z;
	return (party_mix ? black : white);
}

static t_vector	sinwave(t_intersection *inter, t_figures *lst)
{
	double	sinn;
	double	scal;

	scal = lst->wave_length;
	sinn = sin(inter->position.z * scal) + sin(inter->position.y * scal);
	return (vector_rotx(inter->normal_vector, sinn));
}

void		apply_texture(int texture, t_intersection *inter, t_figures *lst)
{
	if (texture == 1)
		inter->color = checkerboard(inter);
	else if (texture == 2)
		inter->normal_vector = sinwave(inter, lst);
	else if (texture == 3)
		inter->color = rainbow(inter);
}
