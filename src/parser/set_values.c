#include "../../minishell.h"

t_cmd	*set_cmd_mem(void)
{
	t_cmd		*new;
	t_cmd_data	*data;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	data = ft_calloc(1, sizeof(t_cmd_data));
	if (!data)
	{
		free(new);
		return (NULL);
	}
	new->info = data;
	return (new);
}

t_cmd_name	*set_cmd_word(t_lexer **lexer)
{
	t_cmd_name	*new;

	new = ft_calloc(1, sizeof(t_cmd_name));
	if (!new)
	{
		ft_lstclear((t_list **)&new, free);
		return (NULL);
	}
	new->name = ft_strdup((*lexer)->content->value);
	if (!new->name)
	{
		ft_lstclear((t_list **)&new, free);
		free(new);
		return (NULL);
	}
	return (new);
}

t_cmd_red	*set_cmd_redir(t_lexer **lexer)
{
	t_cmd_red	*new;
	t_cmd_dred	*data;

	new = ft_calloc(1, sizeof(t_cmd_red));
	if (!new)
		return (ft_lstclear((t_list **)&new, free), NULL);
	data = ft_calloc(1, sizeof(t_cmd_dred));
	if (!data)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	new->content = data;
	if ((*lexer)->next && (*lexer)->next->content->key == WORD)
		data->where = ft_strdup((*lexer)->next->content->value);
	if (!data->where)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	data->type = (*lexer)->content->key;
	return (new);
}

int	set_cmd_value(t_lexer **lexer, t_cmd *cmd)
{
	t_cmd_name	*new_word;
	t_cmd_red	*new_redir;
	int			status;

	if ((*lexer)->content->key == WORD)
	{
		new_word = set_cmd_word(lexer);
		if (!new_word)
			return (free_cmd(cmd), printf("WORD ERROR \n"), 1);
		ft_lstadd_back((t_list **)&cmd->info->word, (t_list *)new_word);
		status = WORD;
	}
	else if ((*lexer)->content->key == PIPE)
		status = PIPE;
	else
	{
		new_redir = set_cmd_redir(lexer);
		if (!new_redir)
			return (free_cmd(cmd), printf("REDIR ERROR \n"), 1);
		ft_lstadd_back((t_list **)&cmd->info->redir, (t_list *)new_redir);
		status = REDIR;
	}
	return (status);
}
