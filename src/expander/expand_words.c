#include "../../minishell.h"

t_cmd_name	*expand_name(t_cmd_name *word, t_env *env, t_cmd *cmd)
{
	t_cmd_name	*new;

	while (cmd->info->word)
	{
		new = ft_calloc(1, sizeof(t_cmd_name));
		if (!new)
			return (ft_lstclear((t_list **)&new, free), NULL);
		new->name = expand_value(cmd->info->word->name, env);
		printf("new->name: %s\n", new->name);
		if (!new->name)
			return (ft_lstclear((t_list **)&new, free), free(new), NULL);
		ft_lstadd_back((t_list **)&word, (t_list *)new);
		cmd->info->word = cmd->info->word->next;
	}
	return (word);
}