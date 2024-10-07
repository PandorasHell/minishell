/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:14:11 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/23 22:27:39 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*big_list;

	big_list = (t_list *)malloc(sizeof(t_list) * 1);
	if (!big_list)
		return (0);
	big_list->content = content;
	big_list->next = NULL;
	return (big_list);
}
