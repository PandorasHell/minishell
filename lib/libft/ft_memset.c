/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 03:25:56 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/12 03:25:56 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//# include "stdio.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = c;
	return (s);
}

/*int main()
{
    char str[50];
    strcpy(str, "This is a test string");
    printf("Before: %s\n", str);
    
    ft_memset(str, '$', 7);
    
    printf("After: %s\n", str);
    
    return 0;
}*/