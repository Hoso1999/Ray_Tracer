/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:28:12 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/23 16:26:06 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new_item;

	if (!(new_item = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_item->content = content;
	new_item->next = NULL;
	return (new_item);
}
