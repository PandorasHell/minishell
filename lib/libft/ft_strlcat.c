/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 06:18:12 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/25 15:58:13 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src) + size);
	while (dst[i] && i < size)
		i++;
	k = i;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (k < size)
		dst[i] = '\0';
	return (k + ft_strlen(src));
}

/*int main(void)
{
	char s1[16] = "Hello";
	char *s2 = " World!";
	size_t size = 13;
	printf("%s\n", s1);
	ft_strlcat(s1, s2, size);
	printf("%s\n", s1);
	return (0);
}*/