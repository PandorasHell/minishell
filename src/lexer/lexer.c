#include "../../minishell.h"

/**
 * @brief Set de value of the words in the lexer structure and set the key for each word based on the first character 
 * @param words The words structure to be analyzed to set the lexer key and value
 * @param new The lexer structure to be set with the key and value of the words
 */

static void	set_lexer_key(t_lword *words, t_lexer *new)
{
	t_dlexer	*data;

	data = ft_calloc(1, sizeof(t_dlexer));
	if (!data)
		return ;
	new->content = data;
	data->value = ft_strdup(words->word);
	data->key = WORD;
	if (data->value[0] == '|')
		data->key = PIPE;
	else if (data->value[0] == '<' && data->value[1])
		data->key = HEREDOC;
	else if (data->value[0] == '<')
		data->key = INFILE;
	else if (data->value[0] == '>' && data->value[1])
		data->key = APPEND;
	else if (data->value[0] == '>')
		data->key = OUTFILE;
	else if (data->value[0] == ';')
		data->key = 6;
	else if (data->value[0] == '&')
		data->key = 7;
	if ((data->value[0] == '|' && data->value[1])
		|| (data->value[0] == '&' && data->value[1]))
		data->key = -1;
}

/**
 * @brief Set the lexer value for each word in the line
 * @param words The words to be analyzed to set the lexer value
 * @param lexer The lexer structure to be set
 * @return The lexer structure with the words and their values set or NULL if an error occurs
 */

static t_lexer	*set_lexer_value(t_lword *words, t_lexer *lexer)
{
	t_lexer	*new;
	t_lword	*temp_word;

	new = NULL;
	temp_word = words;
	while (words)
	{
		new = ft_calloc(1, sizeof(t_lexer));
		if (!new)
		{
			ft_lstclear((t_list **)&lexer, free);
			return (NULL);
		}
		set_lexer_key(words, new);
		if (new->content->key == -1)
			return (NULL);
		ft_lstadd_back((t_list **)&lexer, (t_list *)new);
		words = words->next;
	}
	ft_lstclear((t_list **)&temp_word, free);
	return (lexer);
}

/**
 * @brief Free the lexer structure and its content from memory
 * @param lexer The lexer structure to be freed
 */

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = (*lexer);
	while ((*lexer))
	{
		(*lexer) = (*lexer)->next;
		free(tmp->content->value);
		free(tmp->content);
		free(tmp);
		tmp = (*lexer);
	}
}

/**
 * @brief Split the line into words and set the lexer value for each of them
 * @param line The line input by the user to be split into words
 * @return The lexer structure with the words and their values set or NULL if an error occurs
 */

t_lexer	*lexical_analysis(char *line)
{
	t_lword	*words;
	t_lexer	*lexer;

	lexer = NULL;
	words = NULL;
	words = split_words(line, words);
	if (!words)
		return (NULL);
	lexer = set_lexer_value(words, lexer);
	return (lexer);
}
