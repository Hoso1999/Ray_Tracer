/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2021/02/19 10:01:48 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_types		g_type_event_arr[MAX_TYPE_SIZE] = {
	{"c", type_char},
	{"s", type_string},
	{"p", type_pointer},
	{"d", type_digit},
	{"i", type_digit},
	{"u", type_unsigned},
	{"x", type_hex},
	{"X", type_upperhex},
	{"%", type_percent}
};

static size_t	ft_filters(va_list *f_args, int c, t_event event)
{
	size_t				count;
	size_t				index;

	index = 0;
	count = 0;
	while (index < MAX_TYPE_SIZE)
	{
		if (*g_type_event_arr[index].symbol == c)
		{
			count += g_type_event_arr[index].type(f_args, event);
			break ;
		}
		++index;
	}
	return (count);
}

static size_t	ft_event_flags(const char *format,
				size_t index, t_event *event, va_list f_flags)
{
	while (*(format + index))
	{
		if (!FT_IS_TYPE_EVENT(*(format + index)) &&
			!FT_IS_FLAG_EVENT(*(format + index)) &&
			!ft_isdigit(*(format + index)))
			break ;
		if (*(format + index) == ZERO_FLAG && !event->width && !event->minus)
			event->zero = 1;
		if (*(format + index) == DOT_FLAG)
			index = ft_event_dot(event, f_flags, index, format);
		if (*(format + index) == MINUS_FLAG)
			*event = ft_event_minus(event);
		if (*(format + index) == STAR_FLAG)
			*event = ft_event_width(event, f_flags);
		if (ft_isdigit(*(format + index)))
			*event = ft_event_digit(event, *(format + index));
		if (FT_IS_TYPE_EVENT(*(format + index)))
		{
			event->type = *(format + index);
			break ;
		}
		++index;
	}
	return (index);
}

static size_t	print_before_conversion(const char *format, size_t *index)
{
	size_t count;

	count = 0;
	while (*(format + *index) != '%' && *(format + *index))
	{
		count += ft_printchar(*(format + *index));
		++(*index);
	}
	return (count);
}

static size_t	format_work(const char *format, t_event *event, va_list *f_args)
{
	size_t count;
	size_t index;

	index = 0;
	count = 0;
	count += print_before_conversion(format, &index);
	while (*(format + index))
	{
		*event = ft_event_init(event);
		if (*(format + index) == '%' && *(format + index + 1))
		{
			index = ft_event_flags(format, ++index, event, *f_args);
			if (FT_IS_TYPE_EVENT(*(format + index)))
			{
				event->count = count;
				count += ft_filters(f_args, event->type, *event);
				++index;
				continue;
			}
		}
		if (*(format + index))
			count += ft_printchar(*(format + index));
		++index;
	}
	return (count);
}

int				ft_printf(const char *format, ...)
{
	va_list		f_args;
	t_event		event;
	size_t		count;

	va_start(f_args, format);
	count = 0;
	count += format_work(format, &event, &f_args);
	va_end(f_args);
	return ((int)count);
}
