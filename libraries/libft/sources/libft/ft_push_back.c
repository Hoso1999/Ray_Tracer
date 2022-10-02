/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:12:28 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/25 18:02:35 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_push_back(t_list **lst, void *content)
{
    // t_list *list;
    t_list *elem;

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
