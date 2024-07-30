/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:22:41 by smeixoei          #+#    #+#             */
/*   Updated: 2023/06/20 17:18:37 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digit(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		number;

	number = ft_digit(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = ft_calloc(number + 1, sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	number--;
	while (n > 0)
	{
		str[number--] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}
