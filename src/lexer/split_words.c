#include "../../minishell.h"

static int quote_checker(const char *line)
{
	int len;

	len = 1;
	if (line[0] == '\'')
	{
		while (line[len] && line[len] != '\'')
			len++;
		if (line[len] == '\'')
			return (len);
	}
	else if (line[0] == '\"')
	{
		while (line[len] && line[len] != '\"')
			len++;
		if (line[len] == '\"')
			return (len);
	}
	return (0);
}

static char *save_word(char *line)
{
	char *word;
	int i;

	i = 0;
	while (line[i] && !is_space(line[i]))
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (line[i] && !is_space(line[i]))
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

t_lword	*split_words(char *line)
{
	t_lword *words;
	t_lword *tmp;
	int i;

	i = 0;
	words = NULL;
	while (line[i])
	{
		if (!is_space(line[i]))
		{
			tmp = ft_calloc(1, sizeof(t_lword));
			if (!tmp)
			{
				ft_lstclear((t_list **)&words, free);
				return (NULL);
			}
			tmp->word = save_word(&line[i]);
			ft_lstadd_back((t_list **)&words, (t_list *)tmp);
		}
		else
			i++;
	}
	return (words);
}