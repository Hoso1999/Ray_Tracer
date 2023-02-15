#ifndef PRINTF_EVENTS_H
#define PRINTF_EVENTS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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

typedef uintptr_t	t_pointer;

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

t_event			ft_event_init(t_event *event);

size_t			ft_event_dot(t_event *event, va_list f_args,
				size_t start, const char *format);

t_event			ft_event_digit(t_event *event, char c);

t_event			ft_event_width(t_event *event, va_list f_args);

t_event			ft_event_minus(t_event *event);



#endif
