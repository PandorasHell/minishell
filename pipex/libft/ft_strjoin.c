/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:19:18 by smeixoei          #+#    #+#             */
/*   Updated: 2024/03/05 19:28:51 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_loop(char *s1, char *s2, char *src)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s1[i] != '\0')
	{
		src[i] = s1[i];
		i++;
	}
	while (s2[y] != '\0')
	{
		src[i] = s2[y];
		i++;
		y++;
	}
	src[i] = '\0';
	return (src);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux_s1;
	char	*aux_s2;
	char	*src;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return ((char *)s2);
	else if (s2 == NULL)
		return ((char *)s1);
	aux_s1 = (char *)s1;
	aux_s2 = (char *)s2;
	src = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!src)
		return (NULL);
	return (ft_loop(aux_s1, aux_s2, src));
}
