#include "../../minishell.h"

int	expand_name(t_cmd *word, t_env *env, t_cmd *cmd)
{
	t_cmd_name	*new;
	t_cmd_name	*tmp;

	tmp = cmd->info->word;
	while (tmp)
	{
		new = ft_calloc(1, sizeof(t_cmd_name));
		if (!new)
		{
			free_cmd(word);
			return (1);
		}
		new->name = expand_value(tmp->name, env);
		if (!new->name)
		{
			free_cmd(word);
			free(new);
			return (1);
		}
		ft_lstadd_back((t_list **)&word->info->word, (t_list *)new);
		tmp = tmp->next;
	}
	return (0);
}
