#include "../../minishell.h"

t_cmd_red	*expand_redir(t_cmd_red *redir, t_env *env, t_cmd *cmd)
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
		data->where = expand_value();
	if (!data->where)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	data->type = cmd->info->redir->content->type;
	return (new);
	// Ahora si hay que recorrer cada nodo la lista t_cmd_red de cada comando y sustituir las expansiones.
	// En este caso ha que comprobar el valor where por si fuera una expansión.
}
