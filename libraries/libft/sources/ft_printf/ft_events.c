/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:37:05 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/27 02:17:19 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_event		ft_event_init(t_event *event)
{
	event->dot = -1;
	event->minus = 0;
	event->type = 0;
	event->width = 0;
	event->zero = 0;
	event->star = 0;
	event->count = 0;
	return (*event);
}

t_event		ft_event_minus(t_event *event)
{
	event->zero = 0;
	event->minus = 1;
	return (*event);
}

t_event		ft_event_width(t_event *event, va_list f_args)
{
	event->star = 1;
	event->width = va_arg(f_args, int);
	if (event->width < 0)
	{
		event->minus = 1;
		event->zero = 0;
		event->width *= -1;
	}
	return (*event);
}

t_event		ft_event_digit(t_event *event, char c)
{
	if (event->star == 1)
		event->width = 0;
	event->width = event->width * 10 + c - ZERO_FLAG;
	return (*event);
}

size_t		ft_event_dot(t_event *event, va_list f_args,
			size_t start, const char *format)
{
	size_t	index;
	int		num;

	index = start;
	++index;
	if (*(format + index) == STAR_FLAG)
	{
		event->dot = va_arg(f_args, int);
		++index;
	}
	else
	{
		num = 0;
		while (ft_isdigit(*(format + index)))
		{
			num *= 10;
			num += *(format + index) - '0';
			++index;
		}
		event->dot = num;
	}
	return (index);
}
