#include "../../minishell.h"

/**
 * @brief Check if the line has a quote and if it is closed
 * @param line The line to be analyzed
 * @return The length of the line if there is a quote, 0 if there is no quote
 */

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

/**
 * @brief While the string is different from spaces and operators and,
 * in the case of having quotes, these are closed, it is saved in a new node
 * @param line The line to be analyzed to save the word
 * @return The new node with the string or NULL if an error occurs
 */

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
			break ;
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

/**
 * @brief If the line has an operator, save it in the list
 * @param line The line to be analyzed to save the operator
 * @return The new node with the operator or NULL if an error occurs
 */

static char	*save_operator(char *line)
{
	char	*word;
	int		len;
	char	operator;

	operator = line[0];
	len = 0;
	while (line[len] && line[len] == operator)
		len++;
	if (len > 2)
		return (NULL);
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, line, len + 1);
	return (word);
}

/**
 * @brief Save the word or operator in the list
 * @param line The line to be analyzed
 * @param tmp The new node to save the word or operator
 * @param i The index of the line
 */

void	save_new(char *line, t_lword *tmp, size_t i)
{
	if (!is_operator(line[i]))
		tmp->word = save_word(&line[i]);
	else if (is_operator(line[i]))
		tmp->word = save_operator(&line[i]);
}

/**
 * @brief Split the line into words and operators and save them in a list
 * @param line The line to be split from the user
 * @param words The words to be analyzed and saved
 * @return The words split or NULL if an error occurs
 */

t_lword	*split_words(char *line, t_lword *words)
{
	t_lword	*tmp;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
		{
			tmp = ft_calloc(1, sizeof(t_lword));
			if (!tmp)
				return ((ft_lstclear((t_list **)&words, free)), NULL);
			save_new(line, tmp, i);
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
