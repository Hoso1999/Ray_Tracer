/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2023/02/14 22:46:33 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	type_string(va_list *p_args, t_event event)
{
	char	*type;
	size_t	count;
	size_t	s_len;

	type = va_arg(*p_args, char *);
	if (!type)
		type = "(null)";
	count = 0;
	if (event.zero)
		return (0);
	s_len = ft_event_strlen(type);
	if (event.dot > -1 && event.dot < (int)s_len)
		s_len = event.dot;
	if (event.minus)
		count += ft_print_max_width(type, s_len + 1);
	count += ft_general_width(event.width - s_len + 1, 1, 0);
	if (!event.minus)
		count += ft_print_max_width(type, s_len + 1);
	return (count);
}

size_t	type_char(va_list *p_args, t_event event)
{
	int		c;
	size_t	count;

	c = va_arg(*p_args, int);
	count = 0;
	if (event.minus)
		count += ft_printchar(c);
	count += ft_general_width(event.width, 1, 0);
	if (!event.minus)
		count += ft_printchar(c);
	return (count);
}
