/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:09:35 by smeixoei          #+#    #+#             */
/*   Updated: 2024/03/05 19:29:02 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	ft_strchr_pos(char const *s, char c)
{
	char	*ptr;
	int		pos_c;

	ptr = ft_strchr(s, (int)c);
	if (ptr == 0)
		pos_c = ft_strlen(s);
	else
		pos_c = ptr - s;
	return (pos_c);
}

static void	*ft_free(char **aux)
{
	int	i;

	i = 0;
	while (aux[i] != (void *)0)
	{
		free(aux[i]);
		i++;
	}
	free(aux);
	return (NULL);
}

static char	**ft_fillarray(char const *s, char c, char **aux)
{
	int	pos_c;
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if ((*s == c) && (*s))
			s++;
		else if (*s != c)
		{
			pos_c = ft_strchr_pos(s, c);
			if (pos_c)
			{
				aux[i] = ft_substr(s, 0, pos_c);
				if (!aux[i])
					return (ft_free(aux));
				i++;
				s += pos_c;
			}
			else
				s++;
		}
	}
	aux[i] = NULL;
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	char	**aux;

	if (s == NULL)
		return (NULL);
	aux = (char **)malloc((ft_words(s, c) + 1) * sizeof(char *));
	if (!aux)
		return (NULL);
	aux = ft_fillarray(s, c, aux);
	return (aux);
}
