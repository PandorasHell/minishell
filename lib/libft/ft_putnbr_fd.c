/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 07:29:54 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/13 07:29:54 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		write(fd, &(char){n % 10 + '0'}, 1);
	}
	else
		write(fd, &(char){n + '0'}, 1);
}

/*int main(void) {
    int n = -123456789;
    int fd = 1; // stdout

    ft_putnbr_fd(n, fd);

    return 0;
}*/
