#include "../../minishell.h"

static void	*free_lexer_key(t_lexer *lexer, t_lexer *new, t_cmd_name *tmp_word,
	t_cmd_name *words)
{
	ft_putstr_fd("Syntax error near unexpected token: ", STDERR_FILENO);
	if (words->name[0] == '|' && words->name[1] == '|')
		ft_putendl_fd("||", STDERR_FILENO);
	else if (words->name[0] == '&' && words->name[1] == '&')
		ft_putendl_fd("&&", STDERR_FILENO);
	else if (words->name[0] == '<' && ft_strlen(words->name) == 2)
		ft_putendl_fd("<", STDERR_FILENO);
	else if (words->name[0] == '<')
		ft_putendl_fd("<<", STDERR_FILENO);
	else if (words->name[0] == '>' && ft_strlen(words->name) == 2)
		ft_putendl_fd(">", STDERR_FILENO);
	else if (words->name[0] == '>')
		ft_putendl_fd(">>", STDERR_FILENO);
	free(new);
	free_lexer(&lexer);
	ft_lstclear((t_list **)&lexer, free);
	ft_lstclear((t_list **)&tmp_word, free);
	return (NULL);
}

static int	set_lexer_key(t_cmd_name *words, t_lexer *new)
{
	t_dlexer	*data;

	if ((words->name[0] == '|' && words->name[1] == '|')
		|| (words->name[0] == '&' && words->name[1] == '&')
		|| (words->name[0] == '<' && ft_strlen(words->name) > 2)
		|| (words->name[0] == '>' && ft_strlen(words->name) > 2))
		return (-1);
	data = ft_calloc(1, sizeof(t_dlexer));
	if (!data)
		return (-1);
	new->content = data;
	data->value = ft_strdup(words->name);
	data->key = WORD;
	if (data->value[0] == '|' && !data->value[1])
		data->key = PIPE;
	else if (data->value[0] == '<' && data->value[1])
		data->key = HEREDOC;
	else if (data->value[0] == '<')
		data->key = INFILE;
	else if (data->value[0] == '>' && data->value[1])
		data->key = APPEND;
	else if (data->value[0] == '>')
		data->key = OUTFILE;
	return (0);
}

// TODO: verificar su correcto funcionamiento

static t_lexer	*set_lexer_value(t_cmd_name *words, t_lexer *lexer)
{
	t_lexer		*new;
	t_cmd_name	*tmp_word;

	new = NULL;
	tmp_word = words;
	while (words)
	{
		new = ft_calloc(1, sizeof(t_lexer));
		if (!new)
		{
			ft_lstclear((t_list **)&lexer, free);
			return (NULL);
		}
		if (set_lexer_key(words, new) == -1)
			return (free_lexer_key(lexer, new, tmp_word, words));
		ft_lstadd_back((t_list **)&lexer, (t_list *)new);
		words = words->next;
	}
	ft_lstclear((t_list **)&tmp_word, free);
	return (lexer);
}

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

t_lexer	*lexical_analysis(char *line)
{
	t_cmd_name	*words;
	t_lexer		*lexer;

	lexer = NULL;
	words = NULL;
	words = split_words(line, words);
	if (!words)
		return (NULL);
	lexer = set_lexer_value(words, lexer);
	return (lexer);
}
