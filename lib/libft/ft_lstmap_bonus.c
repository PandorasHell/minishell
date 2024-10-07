/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:34:18 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/25 16:25:48 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*ptr;

	if (!lst || !f || !del)
		return (0);
	new_list = 0;
	while (lst)
	{
		ptr = f(lst -> content);
		new_node = ft_lstnew(ptr);
		if (!new_node)
		{
			del (ptr);
			ft_lstclear(&new_list, (*del));
			return (0);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst -> next;
	}
	return (new_list);
}
