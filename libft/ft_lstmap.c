/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:39:58 by sutku             #+#    #+#             */
/*   Updated: 2022/10/25 23:17:46 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*arr;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	ptr = lst;
	head = NULL;
	while (ptr)
	{
		arr = malloc(sizeof(t_list));
		if (!arr)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		arr->content = (*f)(ptr->content);
		arr->next = NULL;
		ft_lstadd_back(&head, arr);
		ptr = ptr->next;
	}
	return (head);
}
