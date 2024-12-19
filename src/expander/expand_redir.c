/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:51 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:18:52 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd_red	*set_redir_mem(t_cmd *cmd)
{
	t_cmd_red	*redir;

	redir = ft_calloc(1, sizeof(t_cmd_red));
	if (!redir)
	{
		free_cmd(cmd);
		return (NULL);
	}
	redir->content = ft_calloc(1, sizeof(t_cmd_dred));
	if (!redir->content)
	{
		free(redir);
		free_cmd(cmd);
		return (NULL);
	}
	return (redir);
}

static void	manage_where(char **aux, int *quote, t_cmd_red **new)
{
	if (!*quote)
	{
		free((*new)->content);
		free(*new);
		*new = expand_split_redir(*aux);
		free(*aux);
	}
	else
	{
		(*new)->content->where = ft_strdup(*aux);
		free(*aux);
	}
}

int	expand_redir(t_cmd *redir, t_env *env, t_cmd *cmd)
{
	t_cmd_red	*new;
	t_cmd_red	*tmp;
	int			quote;
	char		*aux;

	tmp = cmd->info->redir;
	while (tmp)
	{
		quote = 0;
		new = set_redir_mem(redir);
		if (tmp->content->type == HEREDOC)
			aux = ft_strdup(tmp->content->where);
		else
			aux = expand_dolar(tmp->content->where, env, &quote);
		manage_where(&aux, &quote, &new);
		if (!new->content->where)
			return (free_cmd(redir), free(new), 1);
		new->content->type = tmp->content->type;
		ft_lstadd_back((t_list **)&redir->info->redir, (t_list *)new);
		tmp = tmp->next;
	}
	return (0);
}
