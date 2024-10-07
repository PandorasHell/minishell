/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 06:12:36 by juan-cas          #+#    #+#             */
/*   Updated: 2023/09/13 06:12:36 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && ft_strrchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_strrchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
