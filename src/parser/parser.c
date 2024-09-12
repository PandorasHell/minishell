#include "../../minishell.h"

void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;
	t_cmd_red *tmp_redir;
	t_cmd_name *tmp_word;

    while (cmd)
    {
        tmp = cmd->next;
        if (cmd->info->word)
            {
				tmp_word = cmd->info->word->next;
				free(cmd->info->word->name);
				free(cmd->info->word);
				cmd->info->word = tmp_word;
			}
        if (cmd->info->redir)
        {
            while (cmd->info->redir)
            {
                tmp_redir = cmd->info->redir->next;
                free(cmd->info->redir->content->where);
                free(cmd->info->redir->content);
                free(cmd->info->redir);
                cmd->info->redir = tmp_redir;
            }
        }
        cmd = tmp;
    }
}

t_cmd	*create_cmd(t_lexer **lexer)
{
	t_cmd	*cmd;
	int	status;

	cmd = NULL;
	cmd = set_cmd_mem(cmd);
	status = 0;
	if (!cmd)
		return (free_cmd(cmd), NULL);
	while (lexer)
	{
		status = set_cmd_value(lexer, cmd);
		if (status == PIPE)
		{
			if ((*lexer)->next)
				(*lexer) = (*lexer)->next;
			return (cmd);
		}
		else if (status == REDIR)
		{
			if ((*lexer)->next)
				(*lexer) = (*lexer)->next;
			else
				return (free_cmd(cmd), printf("NO REDIR ERROR \n"), NULL);
		}
		if ((*lexer)->next && (status == WORD || status == REDIR))
			(*lexer) = (*lexer)->next;
		else
		{
			(*lexer) = (*lexer)->next;
			break ;
		}
	}
	return (cmd);
}

t_cmd	*final_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;
	t_cmd	*new;

	cmd = NULL;
	while (lexer)
	{
		if (lexer->content->key == PIPE)
			return (free_cmd(cmd), printf("PIPE ERROR \n"), NULL);
		new = create_cmd(&lexer);
		if (!new)
			return (free_cmd(cmd), ft_lstclear((t_list **)&cmd, free), NULL);
		ft_lstadd_back((t_list **)&cmd, (t_list *)new);
	}
	return (cmd);
}
