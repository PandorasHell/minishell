/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:20:00 by smeixoei          #+#    #+#             */
/*   Updated: 2023/06/15 19:45:55 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	result;

	i = 0;
	if (haystack == NULL && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while ((haystack[i] != '\0') && (i + ft_strlen(needle) <= len))
	{
		result = ft_strncmp(&haystack[i], needle, ft_strlen(needle));
		if (result == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
