/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:24:16 by hohayrap          #+#    #+#             */
/*   Updated: 2021/07/25 12:04:16 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

list_t	*ft_lstmap(list_t *lst, void *(*f)(void *), void (*del)(void *))
{
	list_t *new_element;
	list_t *new_list;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		if (!(new_element = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}
