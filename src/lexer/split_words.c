#include "../../minishell.h"

static int quote_checker(const char *line)
{
	int len;
	char quote;

	quote = line[0];
	len = 1;
	while (line[len] && line[len] != quote)
		len++;
	if (line[len] == quote)
		return (len + 1);
	return (0);
}

static char *save_word(char *line)
{
	char *word;
	int i;
	int len;
	int quote;

	len = 0;
	quote = 0;
	while (line[len] && !is_space(line[len]) && !is_operator(line[len]))
	{
		if (is_quote(line[len]))
		{
			quote = quote_checker(&line[len]);
			if (!quote)
				return (NULL);
			len += quote;
		}
		else
			len++;
	}
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = line[i];
		i++;
	}
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
			if (is_operator(line[i]))
				tmp->word = ft_substr(&line[i], 0, 1);
			if (!tmp->word)
			{
				ft_lstclear((t_list **)&words, free);
				free(tmp);
				return (NULL);
			}
			ft_lstadd_back((t_list **)&words, (t_list *)tmp);
			i += ft_strlen(tmp->word);
		}
		else
			i++;
	}
	return (words);
}