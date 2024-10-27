#include "../../minishell.h"

/**
 * @brief Set the memory for the command structure
 * with the values expanded from the original command
 * @return The new command structure
 */

t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*exp;
	t_cmd	*new;
	t_cmd	*tmp;

	exp = NULL;
	tmp = cmd;
	while (tmp)
	{
		new = set_cmd_mem();
		if (!new)
		{
			ft_lstclear((t_list **)&exp, free);
			return (NULL);
		}
		if (expand_name(new, env, tmp) || expand_redir(new, env, tmp))
			return (ft_lstclear((t_list **)&exp, free), NULL);
		ft_lstadd_back((t_list **)&exp, (t_list *)new);
		tmp = tmp->next;
	}
	return (exp);
}
