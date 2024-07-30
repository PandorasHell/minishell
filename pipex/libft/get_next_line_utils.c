/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:51:26 by smeixoei          #+#    #+#             */
/*   Updated: 2023/07/26 15:59:31 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*newstring;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s2 && s1)
		return ((char *)s1);
	if (!s1)
		return (NULL);
	newstring = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s1[++i] != '\0')
		newstring[i] = s1[i];
	while (s2[j] != '\0')
		newstring[i++] = s2[j++];
	newstring[i] = '\0';
	free(s1);
	return (newstring);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	s = malloc(count * size);
	if (!s)
		return (0);
	while (i < count * size)
	{
		s[i] = '\0';
		i++;
	}
	return ((void *)s);
}
