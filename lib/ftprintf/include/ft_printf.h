/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:01:38 by hohayrap          #+#    #+#             */
/*   Updated: 2023/02/14 22:46:21 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "printf_events.h"

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

size_t			ft_printchar(char c);

size_t			ft_general_width(int width, int minus, int zero);

size_t			ft_print_max_width(char *str, size_t width);

char			*ft_event_putnbr_base(t_pointer nbr, char *base);

size_t      	ft_event_strlen(const char *s);

void            ft_event_putchar_fd(char c, int fd);

char	        *ft_event_strdup(const char *src);

int             ft_event_isdigit(int c);

char			*ft_event_itoa(int n);

#endif
