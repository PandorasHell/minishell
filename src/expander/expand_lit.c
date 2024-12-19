/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:49 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:18:49 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_lit(char *ret, char *name, int *i)
{
	char	lit[2];

	lit[0] = name[*i];
	lit[1] = '\0';
	ret = ft_strappend(ret, lit);
	(*i)++;
	return (ret);
}
