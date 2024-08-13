/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 07:02:50 by juan-cas          #+#    #+#             */
/*   Updated: 2024/05/22 04:27:51 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int 	ft_countword(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	cleanup(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}

char	**filler(const char *s, char **lst, char c)
{
	size_t	word_len;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			word_len = 0;
			while (s[word_len] != '\0' && s[word_len] != c)
				word_len++;
			lst[i] = (char *)malloc(sizeof(char) * (word_len + 1));
			if (!lst[i])
			{
				return (cleanup(lst), NULL);
			}
			ft_strlcpy(lst[i], s, word_len + 1);
			i++;
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	int		wordcount;

	if (s == NULL)
		return (NULL);
	wordcount = ft_countword(s, c);
	lst = (char **)malloc((wordcount + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	if (!filler(s, lst, c))
		return (NULL);
	return (lst);
}
