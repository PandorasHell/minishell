/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 06:17:09 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/12 06:17:09 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_b;
	unsigned char	*src_b;

	if (!dest && !src)
		return (0);
	dest_b = (unsigned char *) dest;
	src_b = (unsigned char *) src;
	while (n--)
		*dest_b++ = *src_b++;
	return (dest);
}
