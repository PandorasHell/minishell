#include "../../minishell.h"

t_cmd_red	*expand_split_redir(char *name)
{
	t_cmd_red	*exp;
	t_cmd_red	*new;
	char		**split_words;
	int			i;

	#TODO: cambiar los : del split por ' '
	split_words = ft_split(name, ':');
	if (!split_words)
		return (NULL);
	exp = NULL;
	i = 0;
	while (split_words[i])
	{
		new = ft_calloc(1, sizeof(t_cmd_red));
		if (!new)
		{
			cleanup(split_words);
			return (NULL);
		}
		new->content = ft_calloc(1, sizeof(t_cmd_dred));
		if (!new->content)
		{
			cleanup(split_words);
			free(new);
			return (NULL);
		}
		new->content->where = ft_strdup(split_words[i]);
		if (!new->content->where)
		{
			cleanup(split_words);
			free(new->content);
			free(new);
			return (NULL);
		}
		new->content->where = expand_quote(new->content->where);
		ft_lstadd_back((t_list **)&exp, (t_list *)new);
		i++;
	}
	cleanup(split_words);
	return (exp);
}

t_cmd_name	*expand_split_word(char *name)
{
	t_cmd_name	*exp;
	t_cmd_name	*new;
	char		**split_words;
	int			i;

	split_words = ft_split(name, ':');
	if (!split_words)
		return (NULL);
	exp = NULL;
	i = 0;
	while (split_words[i])
	{
		new = ft_calloc(1, sizeof(t_cmd_name));
		if (!new)
		{
			cleanup(split_words);
			ft_lstclear((t_list **)&new, free);
			return (NULL);
		}
		new->name = ft_strdup(split_words[i]);
		if (!new->name)
		{
			cleanup(split_words);
			ft_lstclear((t_list **)&new, free);
			return (NULL);
		}
		new->name = expand_quote(new->name);
		ft_lstadd_back((t_list **)&exp, (t_list *)new);
		i++;
	}
	cleanup(split_words);
	return (exp);
}
