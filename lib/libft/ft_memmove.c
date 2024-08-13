/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 02:32:19 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/21 03:52:13 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*stra;
	char	*strb;

	stra = (char *)str1;
	strb = (char *)str2;
	i = 0;
	if (!str1 && !str2)
		return (NULL);
	if (str1 > str2)
	{
		while (n-- > 0)
			stra[n] = strb[n];
	}
	else
	{
		while (i < n)
		{
			stra[i] = strb[i];
			i++;
		}
	}
	return (str1);
}
