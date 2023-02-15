/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:28:12 by hohayrap          #+#    #+#             */
/*   Updated: 2021/07/25 12:02:53 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

list_t	*ft_lstnew(void *content)
{
	list_t *new_item;

	if (!(new_item = (list_t *)malloc(sizeof(list_t))))
		return (NULL);
	new_item->content = content;
	new_item->next = NULL;
	return (new_item);
}
