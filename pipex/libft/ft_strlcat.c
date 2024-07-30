/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:46:11 by smeixoei          #+#    #+#             */
/*   Updated: 2023/06/12 15:12:13 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ld;
	size_t	ls;

	i = 0;
	if (size == 0 && dst == 0)
		return (0);
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (size <= ld)
		return (ls + size);
	if (size > 0)
	{
		while (i < size - ld - 1 && src[i] != '\0')
		{
			dst[ld + i] = src[i];
			i++;
		}
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}
