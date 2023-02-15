#include "ft_printf.h"

static size_t		num_len(long num)
{
	size_t		length;

	length = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		++length;
		num = -num;
	}
	while (num > 0)
	{
		++length;
		num /= 10;
	}
	return (length);
}

char				*ft_event_itoa(int n)
{
	size_t	length;
	char	*str;
	long	nb;

	nb = n;
	length = num_len(nb);
	str = (char*)malloc(length + 1);
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	--length;
	if (nb == 0)
		str[0] = '0';
	else if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[length] = '0' + (nb % 10);
		nb /= 10;
		--length;
	}
	return (str);
}
