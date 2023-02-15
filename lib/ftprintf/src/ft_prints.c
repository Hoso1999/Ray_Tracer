/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2023/02/14 22:44:58 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			ft_printchar(char c)
{
	ft_event_putchar_fd(c, 1);
	return (1);
}

static size_t	number_len(t_pointer nbr, size_t size)
{
	size_t				length;

	length = 0;
	while (nbr)
	{
		nbr /= (t_pointer)size;
		++length;
	}
	return (length);
}

char			*ft_event_putnbr_base(t_pointer nbr, char *base)
{
	char				*res;
	size_t				length;
	size_t				size;

	size = ft_event_strlen(base);
	res = NULL;
	if (!nbr)
		return (ft_event_strdup("0"));
	length = number_len(nbr, size);
	if (!(res = malloc(sizeof(char) * (length + 1))))
		return (NULL);
	res[length] = '\0';
	while (nbr)
	{
		res[length - 1] = base[(nbr % (t_pointer)size)];
		nbr /= (t_pointer)size;
		--length;
	}
	return (res);
}

size_t			ft_general_width(int width, int minus, int zero)
{
	size_t count;

	count = 0;
	while (width - minus > 0 && width > 0)
	{
		if (zero)
			ft_printchar('0');
		else
			ft_printchar(' ');
		--width;
		++count;
	}
	return (count);
}

size_t			ft_print_max_width(char *str, size_t width)
{
	size_t count;

	count = 0;
	while (*str && --width)
	{
		ft_event_putchar_fd(*str, 1);
		++str;
		++count;
	}
	return (count);
}
