#include "../../minishell.h"

t_cmd	*set_cmd_mem(t_cmd *cmd)
{
	t_cmd	*new;
	t_icmd	*icmd;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (ft_lstclear((t_list **)&cmd, free), NULL);
	icmd = ft_calloc(1, sizeof(t_icmd));
	if (!icmd)
		return (ft_lstclear((t_list **)&cmd, free), free(new), NULL);
	new->info = icmd;
	return (new);
}

t_dcmd	*set_cmd_word(t_lexer *lexer)
{
	t_dcmd	*new;

	new = ft_calloc(1, sizeof(t_dcmd));
	if (!new)
		return (ft_lstclear((t_list **)&new, free), NULL);
	new->value = ft_strdup(lexer->content->value);
	if (!new->value)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	return (new);
}

t_rcmd	*set_cmd_redir(t_lexer *lexer)
{
	t_rcmd	*new;
	t_drcmd	*data;

	new = ft_calloc(1, sizeof(t_rcmd));
	if (!new)
		return (ft_lstclear((t_list **)&new, free), NULL);
	data = ft_calloc(1, sizeof(t_drcmd));
	if (!data)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	new->content = data;
	if (lexer->next && lexer->next->content->key == WORD)
		data->where = ft_strdup(lexer->next->content->value);
	else
		data->where = ft_strdup("stdout");
	if (!data->where)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	data->type = lexer->content->key;
	return (new);
}

void	set_cmd_value(t_lexer *lexer, t_cmd *cmd)
{
	t_dcmd *new_word;
	t_rcmd *new_redir;

    if (lexer->content->key == WORD)
    {
        new_word = set_cmd_word(lexer);
        if (!new_word)
            return (free_cmd(cmd));
        ft_lstadd_back((t_list **)&cmd->info->word, (t_list *)new_word);
     }
    else if (lexer->content->key == PIPE)
    {
        lexer = lexer->next;
        return ;
    }
    else
    {
        new_redir = set_cmd_redir(lexer);
        if (!new_redir)
            return (free_cmd(cmd));
        ft_lstadd_back((t_list **)&cmd->info->redir, (t_list *)new_redir);
        lexer = lexer->next;
    }
	lexer = lexer->next;
}
