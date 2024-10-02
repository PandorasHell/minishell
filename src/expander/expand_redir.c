#include "../../minishell.h"

int	expand_redir(t_cmd *redir, t_env *env, t_cmd *cmd)
{

	t_cmd_red	*new;
	t_cmd_dred	*data;

	while (cmd->info->redir)
	{	
		new = ft_calloc(1, sizeof(t_cmd_red));
		if (!new)
			return (ft_lstclear((t_list **)&new, free), 1);
		data = ft_calloc(1, sizeof(t_cmd_dred));
		if (!data)
			return (ft_lstclear((t_list **)&new, free), free(new), 1);
		new->content = data;
		data->where = expand_value(cmd->info->redir->content->where, env);
		if (!data->where)
			return (ft_lstclear((t_list **)&new, free), free(new), 1);
		data->type = cmd->info->redir->content->type;
		ft_lstadd_back((t_list **)&redir->info->redir, (t_list *)new);
		cmd->info->redir = cmd->info->redir->next;
	}
	return (0);
}
