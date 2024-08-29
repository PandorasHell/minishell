#include "../../minishell.h"



t_cmd	*create_cmd(t_lexer *lexer, t_cmd *cmd)
{
	t_cmd	*new;

	new = NULL;
	while (lexer)
	{
		new = ft_calloc(1, sizeof(t_cmd));
		if (!new)
			return (ft_lstclear((t_list **)&cmd, free), NULL);
		check_lexer_key(lexer, new);
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
