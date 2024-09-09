#include "../../minishell.h"

void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;
	t_rcmd *tmp_redir;

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
                free(cmd->info->redir->content->where);
                free(cmd->info->redir->content);
                free(cmd->info->redir);
                cmd->info->redir = tmp_redir;
            }
        }
        free(cmd->info);
        free(cmd);
        cmd = tmp;
    }
}

t_cmd	*create_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;

	cmd = set_cmd_mem(cmd);
	if (!cmd)
		return (free_cmd(cmd), NULL);
	while (lexer)
	{
		set_cmd_value(lexer, cmd);

	}
	return (cmd);
}

t_cmd	*final_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;
	t_cmd	*new;

	new = set_cmd_mem(cmd);
	if (!cmd)
		return (free_cmd(cmd), NULL);
	while (lexer)
	{
		if (lexer->content->key == PIPE)
			return (free_cmd(cmd), NULL);
		new = create_cmd(lexer);
		if (!new)
			return (free_cmd(cmd), NULL);
		
		printf("word: %s\n", cmd->info->word->value);
		printf("type: %d\n", xmd->info->redir->content->type);
		printf("where: %s\n", cmd->info->redir->content->where);
		lexer = lexer->next;
		ft_lstadd_back((t_list **)&cmd, (t_list *)new);
	}
	return (cmd);
}
