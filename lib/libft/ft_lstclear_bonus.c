/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:00:45 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/24 23:05:02 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*holder;
	t_list	*checker;

	if (lst && *lst && del)
	{
		checker = (t_list *)*lst;
		while (checker)
		{
			holder = checker->next;
			ft_lstdelone(checker, del);
			checker = holder;
		}
		*lst = NULL;
	}
}
