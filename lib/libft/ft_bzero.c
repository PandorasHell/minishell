/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 05:53:48 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/12 05:53:48 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*sb;

	i = 0;
	sb = (char *) s;
	while (i < n)
	{
		sb[i] = '\0';
		i++;
	}
}
/*
int main (void)
{
	char str[] = "Hello World";
	size_t n = 5;
	ft_bzero(str, n);
	printf("the string is: %s\n", str);
	return (0);
}*/