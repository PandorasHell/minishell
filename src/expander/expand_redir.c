#include "../../minishell.h"

int	expand_redir(t_cmd *redir, t_env *env, t_cmd *cmd)
{
	t_cmd_red	*new;
	t_cmd_dred	*data;
	t_cmd_red	*tmp;
	int			quote;

	tmp = cmd->info->redir;
	while (tmp)
	{
		quote = 0;
		new = ft_calloc(1, sizeof(t_cmd_red));
		if (!new)
			return (free_cmd(redir), 1);
		data = ft_calloc(1, sizeof(t_cmd_dred));
		if (!data)
			return (free_cmd(redir), free(new), 1);
		new->content = data;
		data->where = expand_dolar(tmp->content->where, env, &quote);
		if (quote)
			new = expand_split_redir(new->content->where);
		else
			data->where = expand_quote(data->where);
		if (!data->where)
			return (free_cmd(redir), free(new), 1);
		data->type = tmp->content->type;
		ft_lstadd_back((t_list **)&redir->info->redir, (t_list *)new);
		tmp = tmp->next;
	}
	tmp = redir->info->redir;
	while (tmp)
	{
		printf("tmp->where: %s\n", tmp->content->where);
		tmp = tmp->next;
	}
	return (0);
}
