#include "../../minishell.h"

int	expand_name(t_cmd *word, t_env *env, t_cmd *cmd)
{
	t_cmd_name	*new;
	t_cmd_name	*tmp;
	int			quote;

	tmp = cmd->info->word;
	while (tmp)
	{
		quote = 0;
		new = ft_calloc(1, sizeof(t_cmd_name));
		if (!new)
		{
			free_cmd(word);
			return (1);
		}
		new->name = expand_dolar(tmp->name, env, &quote);
		if (quote)
			new = expand_split_word(new->name);
		else
			new->name = expand_quote(new->name);
		ft_lstadd_back((t_list **)&word->info->word, (t_list *)new);
		tmp = tmp->next;
	}
	return (0);
}
