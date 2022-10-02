/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/27 02:17:37 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	type_pointer(va_list *p_args, t_event event)
{
	t_pointer	pointer;
	size_t		count;
	char		*p_tostr;
	size_t		pointer_len;

	pointer = (t_pointer)va_arg(*p_args, void *);
	p_tostr = ft_putnbr_base(pointer, CONVERT_16);
	pointer_len = ft_strlen(p_tostr);
	count = 0;
	if (event.minus)
	{
		count += ft_print_max_width("0x", 3);
		count += ft_print_max_width(p_tostr, pointer_len + 1);
	}
	count += ft_general_width(event.width - (int)pointer_len - 1, 1, 0);
	if (!event.minus)
	{
		count += ft_print_max_width("0x", 3);
		count += ft_print_max_width(p_tostr, pointer_len + 1);
	}
	free(p_tostr);
	return (count);
}

size_t	type_percent(va_list *p_args, t_event event)
{
	size_t count;

	(void)p_args;
	count = 0;
	if (event.width > 1 && event.zero)
		count += ft_general_width(event.width - 1, 0, 1);
	if (event.width > 1 && !event.zero && !event.minus)
		count += ft_general_width(event.width, 1, 0);
	if (!event.minus)
		count += ft_printchar('%');
	if (event.minus)
		count += ft_printchar('%');
	if (event.width > 1 && event.minus)
		count += ft_general_width(event.width, 1, 0);
	return (count);
}
