#include "../../minishell.h"

t_cmd_name	*expand_split_word(char *name)
{
	t_cmd_name *exp;
	t_cmd_name *new;
    char **split_words;
    int i = 0;

    split_words = ft_split(name, ':');
    if (!split_words)
        return (NULL);
	exp = NULL;
    while (split_words[i])
    {
        new = ft_calloc(1, sizeof(t_cmd_name));
        if (!new)
        {
            cleanup(split_words);
            return (NULL);
        }
        new->name = ft_strdup(split_words[i]);
		if (!new->name)
		{
			cleanup(split_words);
			free(new);
			return (NULL);
		}
		new->name = expand_quote(new->name);
        ft_lstadd_back((t_list **)&exp, (t_list *)new);
        i++;
    }
    cleanup(split_words);
	return (exp);
}
