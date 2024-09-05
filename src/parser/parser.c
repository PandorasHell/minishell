#include "../../minishell.h"

void	set_cmd_mem(t_cmd *cmd)
{
	t_icmd	*icmd;
	t_rcmd	*rcmd;

	icmd = ft_calloc(1, sizeof(t_icmd));
	if (!icmd)
		return (ft_lstclear((t_list **)&cmd, free));
	rcmd = ft_calloc(1, sizeof(t_rcmd));
	if (!rcmd)
		return (ft_lstclear((t_list **)&cmd, free), free(icmd));
	icmd->redir = rcmd;
	icmd->word = NULL;
	cmd->content = icmd;
}

void	set_cmd_redir(t_lexer *lexer, t_rcmd *redir)
{
	t_drcmd	*new;

	new = ft_calloc(1, sizeof(t_drcmd));
	if (!new)
		return (ft_lstclear((t_list **)&redir, free));
	new->where = ft_strdup(lexer->next->content->value);
	if (!new->where)
		return (ft_lstclear((t_list **)&redir, free), free(new));
	new->type = lexer->content->key;
	printf("where: %s\n", new->where);
	printf("type: %d\n", new->type);
	ft_lstadd_back((t_list **)&redir, (t_list *)new);
}


void	set_cmd_word(t_lexer *lexer, t_dcmd *word)
{
	t_dcmd	*new;

	new = ft_calloc(1, sizeof(t_dcmd));
	if (!new)
		return (ft_lstclear((t_list **)&word, free));
	new->value = ft_strdup(lexer->content->value);
	if (!new->value)
		return (ft_lstclear((t_list **)&word, free), free(new));
	printf("word: %s\n", new->value);
	ft_lstadd_back((t_list **)&word, (t_list *)new);
}

// void	set_cmd_value(t_lexer *lexer, t_cmd *cmd)
// {
// 	while (lexer)
// 	{
// 		if (lexer->content->key == WORD)
// 			set_cmd_word(lexer, cmd->content->word);
// 		else if (lexer->content->key == PIPE)
// 			{
// 				lexer = lexer->next;
// 				if (!lexer)
// 					return ;
// 			}
// 		else
// 		{
// 			if (!lexer->next)
// 				return ;
// 			if (lexer->next->content->key == WORD)
// 			{
// 				set_cmd_redir(lexer, cmd->content->redir);
// 				lexer = lexer->next;
// 			}
// 			else
// 				return ;
// 		}
// 		lexer = lexer->next;
// 	}
// }

t_cmd	*create_cmd(t_lexer *lexer, t_cmd *cmd)
{
	t_cmd	*new;

	new = NULL;
	while (lexer)
	{
		new = ft_calloc(1, sizeof(t_cmd));
		if (!new)
			return (ft_lstclear((t_list **)&cmd, free), NULL);
		set_cmd_mem(new);
		set_cmd_value(lexer, new);
		//printf("word: %ss\n", new->content->word->value);
		 printf("word: %s   type: %d   where: %s\n", new->content->word->value, new->content->redir->content->type, new->content->redir->content->where);
		ft_lstadd_back((t_list **)&cmd, (t_list *)new);
		lexer = lexer->next;
	}
	return (new);
}

t_cmd	*final_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = create_cmd(lexer, cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}
