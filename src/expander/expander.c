#include "../../minishell.h"

t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*exp;
	t_cmd	*tmp;

	exp = NULL;
	while (cmd)
	{
		tmp = set_cmd_mem();
		if (!tmp)
		{
			ft_lstclear((t_list **)&cmd, free);
			return (NULL);
		}
		if (expand_name(tmp, env, cmd) || expand_redir(tmp, env, cmd))
			return (ft_lstclear((t_list **)&cmd, free), NULL);
		ft_lstadd_back((t_list **)&exp, (t_list *)tmp);
		cmd = cmd->next;
	}
	return (exp);
}
