/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:12:28 by hohayrap          #+#    #+#             */
/*   Updated: 2021/07/25 12:05:01 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_push_back(list_t **lst, void *content)
{
    // list_t *list;
    list_t *elem;

    // list = *lst;
	elem = ft_lstnew(content);
	if (*lst)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = elem;
		*lst = (*lst)->next;
	}
	else
		*lst = elem;

}
