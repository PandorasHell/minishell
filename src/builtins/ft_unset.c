/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:33:31 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:33:32 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_single_node(t_env *node)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*tmp3;

	if (!node)
		return ;
	tmp = node;
	tmp2 = tmp->next;
	tmp3 = tmp->next->next;
	tmp->next = tmp3;
	free(tmp2->content->key);
	free(tmp2->content->value);
	free(tmp2->content);
	free(tmp2);
}

static void	free_first_node(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return ;
	tmp = node;
	node = node->next;
	free(tmp->content->key);
	free(tmp->content->value);
	free(tmp->content);
	free(tmp);
}

int	ft_unset(char **cmd, t_env *env)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	i = 0;
	j = 0;
	while (cmd[++i])
	{
		tmp = unset_node_search(cmd[i], &j, env);
		if (tmp && j == 0)
			free_first_node(tmp);
		else if (tmp && j > 0)
			free_single_node(tmp);
	}
	tmp = env;
	return (0);
}
