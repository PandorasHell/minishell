/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:07:29 by smeixoei          #+#    #+#             */
/*   Updated: 2023/06/12 15:11:56 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;

	s = malloc((ft_strlen(s1) + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, (char *)s1, ft_strlen(s1) + 1);
	return (s);
}
