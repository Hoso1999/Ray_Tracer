/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filememdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 11:46:12 by hohayrap          #+#    #+#             */
/*   Updated: 2021/07/25 11:46:18 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_filememdel(file_t *file)
{
	if (!file)
		return ;
	ft_vecstrdel(&file->content);
	free(file);
	file = NULL;
}
