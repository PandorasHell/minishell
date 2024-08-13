/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 07:21:38 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/12 07:21:38 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buffer1, const void *buffer2, size_t count)
{
	while (count--)
	{
		if (*(unsigned char *)buffer1 != *(unsigned char *)buffer2)
			return (*(unsigned char *)buffer1 - *(unsigned char *)buffer2);
		buffer1++;
		buffer2++;
	}
	return (0);
}
