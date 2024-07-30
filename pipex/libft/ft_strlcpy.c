/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:03:44 by smeixoei          #+#    #+#             */
/*   Updated: 2023/03/09 16:03:53 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	n;
	unsigned int	i;

	n = 0;
	i = 0;
	while (src[i] != '\0')
		i++;
	if (size != 0)
	{
		while (src[n] != '\0' && n < (size - 1))
		{
			dest[n] = src[n];
			n++;
		}
		dest[n] = '\0';
	}
	return (i);
}
