#include "../../minishell.h"

int	expand_redir(t_cmd *redir, t_env *env, t_cmd *cmd)
{
	t_cmd_red	*new;
	t_cmd_dred	*data;
	t_cmd_red	*tmp;

	tmp = cmd->info->redir;
	while (tmp)
	{
		new = ft_calloc(1, sizeof(t_cmd_red));
		if (!new)
			return (free_cmd(redir), 1);
		data = ft_calloc(1, sizeof(t_cmd_dred));
		if (!data)
			return (free_cmd(redir), free(new), 1);
		new->content = data;
		data->where = expand_dolar(tmp->content->where, env);
		data->where = expand_quote(data->where);
		if (!data->where)
			return (free_cmd(redir), free(new), 1);
		data->type = tmp->content->type;
		ft_lstadd_back((t_list **)&redir->info->redir, (t_list *)new);
		tmp = tmp->next;
	}
	return (0);
}
