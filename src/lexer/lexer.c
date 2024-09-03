#include "../../minishell.h"

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
	else if (data->value[0] == '<')
		data->key = INFILE;
	else if (data->value[0] == '<' && data->value[1])
		data->key = HEREDOC;
	else if (data->value[0] == '>')
		data->key = OUTFILE;
	else if (data->value[0] == '>' && data->value[1])
		data->key = APPEND;
	else if (data->value[0] == ';')
		data->key = 6;
	else if (data->value[0] == '&')
		data->key = 7;
	if ((data->value[0] == '|' && data->value[1])
		|| (data->value[0] == '&' && data->value[1]))
		data->key = -1;
}

static t_lexer	*set_lexer_value(t_lword *words, t_lexer *lexer)
{
	t_lexer	*new;

	new = NULL;
	while (words)
	{
		new = ft_calloc(1, sizeof(t_lexer));
		if (!new)
			return (ft_lstclear((t_list **)&lexer, free), NULL);
		set_lexer_key(words, new);
		if (new->content->key == -1)
			return (NULL);
		ft_lstadd_back((t_list **)&lexer, (t_list *)new);
		words = words->next;
	}
	return (lexer);
}

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
