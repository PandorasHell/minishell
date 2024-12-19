/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:44 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:18:44 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_exit_code(char *ret, int *i)
{
	char	*tmp;

	tmp = ft_itoa(g_handler);
	ret = ft_strappend(ret, tmp);
	free(tmp);
	(*i)++;
	return (ret);
}
