/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:46 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:18:46 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_dolar_heredoc(char *name, t_env *env)
{
	char	*ret;
	int		i;

	ret = ((i = 0), ft_strdup(""));
	while (name[i])
	{
		if (name[i] == '$')
		{
			i++;
			if (name[i] == '?')
				ret = expand_exit_code(ret, &i);
			else if (is_sys_var(name, &i))
				ret = expand_env(ret, name, &i, env);
			else
			{
				i++;
				ret = expand_lit(ret, name, &i);
			}
		}
		else
			ret = expand_lit(ret, name, &i);
		if ((size_t)i >= ft_strlen(name))
			break ;
	}
	return (ret);
}
