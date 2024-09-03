#include "../../minishell.h"

void	set_cmd_mem(t_lexer *lexer, t_cmd *cmd)
{
	t_icmd	*icmd;
	t_dcmd	*dcmd;
	t_rcmd	*rcmd;

	icmd = ft_calloc(1, sizeof(t_icmd));
	if (!icmd)
		return (ft_lstclear((t_list **)&cmd, free));
	dcmd = ft_calloc(1, sizeof(t_dcmd));
	if (!dcmd)
		return (ft_lstclear((t_list **)&cmd, free), free(icmd));
	rcmd = ft_calloc(1, sizeof(t_rcmd));
	if (!rcmd)
		return (ft_lstclear((t_list **)&cmd, free), free(icmd), free(dcmd));
	icmd->word = dcmd;
	icmd->redir = rcmd;
	cmd->content = icmd;
}

t_cmd	*create_cmd(t_lexer *lexer, t_cmd *cmd)
{
	t_cmd	*new;

	new = NULL;
	while (lexer)
	{
		new = ft_calloc(1, sizeof(t_cmd));
		if (!new)
			return (ft_lstclear((t_list **)&cmd, free), NULL);
		set_cmd_mem(lexer, new);
		make_cmd(lexer, new);
		ft_lstadd_back((t_list **)&cmd, (t_list *)new);
		lexer = lexer->next;
	}
	return (new);
}

t_cmd	*final_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;

	cmd = create_cmd(lexer, cmd);
	return (cmd);
}
