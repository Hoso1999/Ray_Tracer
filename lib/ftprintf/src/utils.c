#include "ft_printf.h"

int ft_event_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char	*ft_event_strdup(const char *src)
{
	size_t	size;
	size_t	index;
	char	*str;

	size = ft_event_strlen(src);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	index = 0;
	while (src[index])
	{
		str[index] = src[index];
		++index;
	}
	str[index] = '\0';
	return (str);
}

void	ft_event_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

size_t	ft_event_strlen(const char *s)
{
	size_t index;

	index = 0;
	while (s[index])
		++index;
	return (index);
}
