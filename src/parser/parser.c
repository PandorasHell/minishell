/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:13 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:25:22 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd		*tmp;
	t_cmd_red	*tmp_redir;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->info->word)
			ft_lstclear((t_list **)&cmd->info->word, free);
		if (cmd->info->redir)
		{
			while (cmd->info->redir)
			{
				tmp_redir = cmd->info->redir->next;
				if (cmd->info->redir->content->where)
					free(cmd->info->redir->content->where);
				free(cmd->info->redir->content);
				free(cmd->info->redir);
				cmd->info->redir = tmp_redir;
			}
		}
		cmd = tmp;
	}
}

static t_cmd	*create_cmd(t_lexer **lexer)
{
	t_cmd	*cmd;
	int		status;

	cmd = NULL;
	status = 0;
	cmd = set_cmd_mem();
	if (!cmd)
		return (free_cmd(cmd), NULL);
	while (lexer)
	{
		status = set_cmd_value(lexer, cmd);
		if (status == -1)
			return (free_cmd(cmd), ft_lstclear((t_list **)&cmd, free), NULL);
		if (status_pipe(lexer, status))
			return (cmd);
		if (status_redir(lexer, status, cmd))
			return (NULL);
		if ((*lexer)->next && (status == WORD || status == REDIR))
			(*lexer) = (*lexer)->next;
		else
			return ((*lexer) = (*lexer)->next, cmd);
	}
	return (cmd);
}

t_cmd	*complete_parser(t_lexer *lexer)
{
	t_cmd	*cmd;
	t_cmd	*new;

	cmd = NULL;
	while (lexer)
	{
		if (lexer->content->key == PIPE)
		{
			free_cmd(cmd);
			ft_lstclear((t_list **)&cmd, free);
			printf("PIPE ERROR \n");
			return (NULL);
		}
		new = create_cmd(&lexer);
		if (!new)
		{
			free_cmd(cmd);
			ft_lstclear((t_list **)&cmd, free);
			return (NULL);
		}
		ft_lstadd_back((t_list **)&cmd, (t_list *)new);
	}
	free_lexer(&lexer);
	return (cmd);
}
