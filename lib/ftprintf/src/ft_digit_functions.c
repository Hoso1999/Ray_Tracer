/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:34:33 by hohayrap          #+#    #+#             */
/*   Updated: 2023/02/14 22:44:27 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		unum_len(t_pointer num)
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

char				*ft_uitoa(t_pointer n)
{
	size_t		length;
	char		*str;
	t_pointer	nb;

	nb = n;
	length = unum_len(nb);
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

static size_t		lnum_len(long num)
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

char				*ft_ltoa(long n)
{
	size_t	length;
	char	*str;
	long	nb;

	nb = n;
	length = lnum_len(nb);
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
