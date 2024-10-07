/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:38:11 by juan-cas          #+#    #+#             */
/*   Updated: 2024/05/28 13:37:34 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*b;
	char	*l;

	if (*little == 0)
		return ((char *)big);
	l = (char *)little;
	while (*big && len > 0)
	{
		b = (char *)big;
		i = len;
		while (*big && *little && *big == *little && len-- > 0)
		{
			big++;
			little++;
		}
		if (!*little)
			return (b);
		big = ++b;
		little = l;
		len = --i;
	}
	return (NULL);
}
