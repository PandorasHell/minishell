/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:26:01 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/21 03:36:51 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t number, size_t size)
{
	void	*str;

	str = (void *)malloc(number * size);
	if (!str)
		return (NULL);
	ft_memset(str, 0, number * size);
	return (str);
}

/*int main(void)
{
	return (0);
}*/