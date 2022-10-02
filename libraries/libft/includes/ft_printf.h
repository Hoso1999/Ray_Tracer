/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/27 02:18:30 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define MAX_TYPE_SIZE 9
# define MIN_PREC 6
# define CONVERT_16 "0123456789abcdef"
# define CONVERTUP_16 "0123456789ABCDEF"
# define ZERO_FLAG '0'
# define MINUS_FLAG '-'
# define DOT_FLAG '.'
# define STAR_FLAG '*'
# define EXP_BASE "e-01"
# define FT_IS_FLAG_EVENT(c) (c == '-' || c == '0' || c == '.' || c == '*')
# define FT_IS_TYPE_EVENT(c) (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')

typedef unsigned long long int	t_pointer;

typedef	struct	s_event
{
	int			width;
	int			zero;
	int			type;
	int			minus;
	int			dot;
	int			star;
	int			count;
}				t_event;

typedef struct	s_float
{
	long		int_part;
	long		float_part;
	int			prec;
}				t_float;

typedef struct	s_types
{
	char		*symbol;
	size_t		(*type)(va_list *p_args, t_event event);
}				t_types;

char			*ft_uitoa(t_pointer n);

int				ft_printf(const char *format, ...);

size_t			type_char(va_list *p_args, t_event event);

size_t			type_string(va_list *p_args, t_event event);

size_t			type_pointer(va_list *p_args, t_event event);

size_t			type_digit(va_list *p_args, t_event event);

size_t			type_integer(va_list *p_args, t_event event);

size_t			type_unsigned(va_list *p_args, t_event event);

size_t			type_hex(va_list *p_args, t_event event);

size_t			type_upperhex(va_list *p_args, t_event event);

size_t			type_percent(va_list *p_args, t_event event);

t_event			ft_event_init(t_event *event);

size_t			ft_event_dot(t_event *event, va_list f_args,
				size_t start, const char *format);

t_event			ft_event_digit(t_event *event, char c);

t_event			ft_event_width(t_event *event, va_list f_args);

t_event			ft_event_minus(t_event *event);

size_t			ft_printchar(char c);

size_t			ft_general_width(int width, int minus, int zero);

size_t			ft_print_max_width(char *str, size_t width);

char			*ft_putnbr_base(t_pointer nbr, char *base);

#endif
