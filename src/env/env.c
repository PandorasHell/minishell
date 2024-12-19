/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:45 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:19:46 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->content->key);
		free((*env)->content->value);
		free((*env)->content);
		free(*env);
		*env = tmp;
	}
}

void	save_data_env(t_env *tmp, char **env, int i)
{
	t_denv	*data;

	data = (t_denv *)malloc(sizeof(t_denv));
	if (!data)
		return ;
	tmp->content = data;
	data->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
	data->value = ft_strdup(ft_strchr(env[i], '=') + 1);
}

t_env	*save_env(char **env)
{
	t_env	*lst;
	t_env	*tmp;
	int		i;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		if (!tmp)
		{
			perror("Error creating env list");
			ft_lstclear((t_list **)&lst, free);
			return (NULL);
		}
		save_data_env(tmp, env, i);
		ft_lstadd_back((t_list **)&lst, (t_list *)tmp);
		i++;
	}
	return (lst);
}
