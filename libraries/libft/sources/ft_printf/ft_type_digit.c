/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_digit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/27 02:17:30 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_digit(char *d_tostr, int digit, t_event event)
{
	size_t	count;
	int		d_len;

	d_len = (int)ft_strlen(d_tostr);
	count = 0;
	if (digit < 0 && event.dot >= 0)
		ft_printchar(MINUS_FLAG);
	if (event.dot >= 0)
		count += ft_general_width(event.dot - 1, d_len - 1, 1);
	count += ft_print_max_width(d_tostr, (size_t)d_len + 1);
	return (count);
}

static size_t	digits(char *d_tostr, int digit, t_event event)
{
	size_t	count;
	int		d_len;

	d_len = (int)ft_strlen(d_tostr);
	count = 0;
	if (event.minus)
		count += print_digit(d_tostr, digit, event);
	if (event.dot >= 0 && event.dot < d_len)
		event.dot = d_len;
	if (event.dot >= 0)
	{
		event.width -= event.dot;
		count += ft_general_width(event.width, 0, 0);
	}
	else
		count += ft_general_width(event.width, d_len, event.zero);
	if (!event.minus)
		count += print_digit(d_tostr, digit, event);
	return (count);
}

static size_t	get_digit(int num, t_event event)
{
	int		digit;
	char	*d_tostr;
	size_t	count;

	digit = num;
	count = 0;
	if (digit == 0 && !event.dot)
		return (ft_general_width(event.width, 0, 0));
	if (num < 0 && (event.dot >= 0 || event.zero))
	{
		if (event.zero && event.dot == -1)
			ft_printchar(MINUS_FLAG);
		num *= -1;
		--event.width;
		event.zero = 1;
		++count;
	}
	d_tostr = ft_itoa(num);
	count += digits(d_tostr, digit, event);
	free(d_tostr);
	return (count);
}

size_t			type_digit(va_list *p_args, t_event event)
{
	int		digit;
	size_t	count;

	count = 0;
	digit = va_arg(*p_args, int);
	count += get_digit(digit, event);
	return (count);
}
