#include "../../minishell.h"

static int	quote_checker(const char *line)
{
	int		len;
	char	quote;

	quote = line[0];
	len = 1;
	while (line[len] && line[len] != quote)
		len++;
	if (line[len] == quote)
		return (len + 1);
	return (0);
}

static char	*save_word(char *line)
{
	char	*word;
	int		len;
	int		quote;

	len = 0;
	quote = 0;
	while (line[len] && !is_space(line[len]) && !is_operator(line[len]))
	{
		if (is_quote(line[len]))
		{
			quote = quote_checker(&line[len]);
			if (!quote)
				return (printf("Error: Unclosed quotes\n"), NULL);
			len += quote;
		}
		else
			len++;
	}
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (printf("Error: Malloc fail\n"), NULL);
	ft_strlcpy(word, line, len + 1);
	return (word);
}

static char	*save_operator(char *line)
{
	char	*word;
	int		len;
	char	operator;

	operator = line[0];
	len = 0;
	while (line[len] && line[len] == operator)
		len++;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, line, len + 1);
	return (word);
}

static void	save_new(char *line, t_cmd_name *tmp, size_t i)
{
	if (!is_operator(line[i]))
		tmp->name = save_word(&line[i]);
	else if (is_operator(line[i]))
		tmp->name = save_operator(&line[i]);
}

t_cmd_name	*split_words(char *line, t_cmd_name *words)
{
	t_cmd_name	*tmp;
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
		{
			tmp = ft_calloc(1, sizeof(t_cmd_name));
			if (!tmp)
				return ((ft_lstclear((t_list **)&words, free)), NULL);
			save_new(line, tmp, i);
			if (!tmp->name)
			{
				ft_lstclear((t_list **)&words, free);
				free(tmp);
				return (NULL);
			}
			ft_lstadd_back((t_list **)&words, (t_list *)tmp);
			i += ft_strlen(tmp->name);
		}
		else
			i++;
	}
	return (words);
}
