/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:14:45 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/23 22:28:14 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*holder;

	i = 0;
	holder = (t_list *)lst;
	while (holder)
	{
		i++;
		holder = holder->next;
	}
	return (i);
}
