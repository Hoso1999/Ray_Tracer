/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_udigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2023/02/14 22:46:40 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_udigit(char *u_tostr, int u_len, t_event event)
{
	size_t count;

	count = 0;
	if (event.dot >= 0)
		count += ft_general_width(event.dot - 1, u_len - 1, 1);
	count += ft_print_max_width(u_tostr, (size_t)u_len + 1);
	return (count);
}

static size_t	udigits(char *u_tostr, int u_len, t_event event)
{
	size_t count;

	count = 0;
	if (event.minus)
		count += get_udigit(u_tostr, u_len, event);
	if (event.dot >= 0 && event.dot < u_len)
		event.dot = u_len;
	if (event.dot >= 0)
	{
		event.width -= event.dot;
		count += ft_general_width(event.width, 0, 0);
	}
	else
		count += ft_general_width(event.width, u_len, event.zero);
	if (!event.minus)
		count += get_udigit(u_tostr, u_len, event);
	return (count);
}

size_t			type_unsigned(va_list *p_args, t_event event)
{
	unsigned int	udigit;
	char			*u_tostr;
	int				u_len;
	size_t			count;

	count = 0;
	udigit = va_arg(*p_args, unsigned int);
	if (udigit == 0 && !event.dot)
		return (ft_general_width(event.width, 0, 0));
	u_tostr = ft_uitoa(udigit);
	u_len = (int)ft_event_strlen(u_tostr);
	count += udigits(u_tostr, u_len, event);
	free(u_tostr);
	return (count);
}
