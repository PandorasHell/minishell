#include "../../minishell.h"

/**
 * @brief Set the memory for the name structure
 * @param cmd The command structure to be freed if the memory allocation fails
 * @return The new name structure
 */

static t_cmd_name	*set_name_mem(t_cmd *cmd)
{
	t_cmd_name	*new;

	new = ft_calloc(1, sizeof(t_cmd_name));
	if (!new)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (new);
}

/**
 * @brief Expand the names of the command
 * @param word The name structure to be allocated and filled
 * @param env The environment variables
 * @param cmd The command structure to compare for creating the names
 * @return 0 on success, 1 on failure
 */

int	expand_name(t_cmd *word, t_env *env, t_cmd *cmd)
{
	t_cmd_name	*new;
	t_cmd_name	*tmp;
	int			quote;
	char		*aux;

	tmp = cmd->info->word;
	while (tmp)
	{
		quote = 0;
		new = set_name_mem(cmd);
		if (!new)
			return (1);
		aux = expand_dolar(tmp->name, env, &quote);
		if (quote)
		{
			free(new);
			new = expand_split_word(aux);
			free(aux);
		}
		else
			new->name = expand_quote(aux);
		ft_lstadd_back((t_list **)&word->info->word, (t_list *)new);
		tmp = tmp->next;
	}
	return (0);
}
