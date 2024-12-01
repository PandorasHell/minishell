/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:21:24 by juan-cas          #+#    #+#             */
/*   Updated: 2023/10/14 01:41:22 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *n)
{
	t_list	*holder;

	if (!lst || !n)
		return ;
	if (!(*lst))
		*lst = n;
	else
	{
		holder = *lst;
		while (holder->next)
			holder = holder->next;
		holder->next = n;
	}
}
