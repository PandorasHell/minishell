/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:41 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:18:41 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_exp_env(char *name, int *i, t_env *env)
{
	size_t	len;

	len = ft_strlen(env->content->key);
	if (ft_strncmp(env->content->key, &name[*i], len) == 0
		&& (name[*i + len] == '\0'
			|| ft_strchr("_-?=/.@!^+%*#&()[]{}<>|;:,.~`\\\"'", name[*i + len])))
		return (1);
	else
		return (0);
}

char	*expand_env(char *ret, char *name, int *i, t_env *env)
{
	int		expanded;

	expanded = 0;
	while (env)
	{
		if (check_exp_env(name, i, env))
		{
			ret = ft_strappend(ret, env->content->value);
			expanded = 1;
			*i += ft_strlen(env->content->key);
			break ;
		}
		env = env->next;
	}
	if (!expanded)
	{
		ret = ft_strappend(ret, "");
		while (name[*i] && name[*i] != ' ')
			(*i)++;
	}
	return (ret);
}
