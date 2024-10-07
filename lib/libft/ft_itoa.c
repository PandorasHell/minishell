/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:18:12 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/21 03:36:00 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0 || n < 0)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

static char	*zero(char *str)
{
	str = ft_calloc(2, 1);
	if (!str)
		return (NULL);
	str[0] = '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = "0";
	i = count(n);
	if (n == 0)
	{
		str = zero(str);
		return (str);
	}
	str = ft_calloc(count(n), 1);
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	i--;
	while (n != 0)
	{
		if (n < 0)
			str[--i] = -(n % 10) + '0';
		else
			str[--i] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

/*int	main(void)
{
	int i = 214783648;
	char *result = ft_itoa(i);
	printf("the string is:%s\n", result);
	return (0);
}*/