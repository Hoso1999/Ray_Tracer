/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 10:59:18 by mgarcia-          #+#    #+#             */
/*   Updated: 2021/03/31 21:18:11 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		in_range(double nb, double min, double max, char *function)
{
	char	error_message[100];

	if (nb < min || nb > max)
	{
		ft_strncpy(error_message, function, 76);
		ft_strcat(error_message, " parameter out of range\n");
		scene_error(error_message);
	}
}

void		next(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}

void		comma(char **str)
{
	if (**str != ',')
		scene_error("parameters bad formatted\n");
	(*str)++;
}

t_vector		parse_vector(char **str)
{
	t_vector	vector;

	vector.x = file_atof(str);
	comma(str);
	vector.y = file_atof(str);
	comma(str);
	vector.z = file_atof(str);
	next(str);
	return (vector);
}

int			parse_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	r |= file_atoi(str);
	in_range(r, 0, 255, "colors must be in range [0, 255],");
	r <<= 16;
	comma(str);
	g |= file_atoi(str);
	in_range(g, 0, 255, "colors must be in range [0, 255],");
	g <<= 8;
	comma(str);
	b |= file_atoi(str);
	in_range(b, 0, 255, "colors must be in range [0, 255],");
	return (r | g | b);
}
