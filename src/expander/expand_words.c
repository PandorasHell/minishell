#include "../../minishell.h"

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

int	expand_name(t_cmd *word, t_env *env, t_cmd *cmd)
{
	t_cmd_name	*new;
	t_cmd_name	*tmp;
	int			quote;
	int		split;
	char		*aux;

	tmp = cmd->info->word;
	while (tmp)
	{
		quote = 0;
		split = 0;
		new = set_name_mem(cmd);
		if (!new)
			return (1);
		aux = expand_dolar(tmp->name, env, &quote, &split);
		if (split && !quote)
		{
			free(new);
			new = expand_split_word(aux);
			free(aux);
		}
		else
		{
			new->name = expand_quote(aux);
		}
		printf("new->name: %s\n", new->name);
		ft_lstadd_back((t_list **)&word->info->word, (t_list *)new);
		tmp = tmp->next;
	}
	return (0);
}
