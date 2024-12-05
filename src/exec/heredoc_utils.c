#include "../../minishell.h"

void	free_redir(t_cmd_red *redir)
{
	t_cmd_red	*tmp;
	t_cmd_red	*aux;

	if (!redir)
		return ;
	tmp = redir;
	while (tmp)
	{
		aux = tmp->next;
		if (tmp->content)
		{
			if (tmp->content->type == HEREDOC)
				unlink(tmp->content->where);
			if (tmp->content->where)
				free(tmp->content->where);
			free(tmp->content);
		}
		free(tmp);
		tmp = aux;
	}
}

char	*remove_quotes(char *limiter)
{
	char	*aux;
	char	quote;
	int		i;

	aux = ft_strdup("");
	if (!aux)
		return (NULL);
	quote = 0;
	i = 0;
	while (limiter && limiter[i])
	{
		if (!quote && (limiter[i] == '\'' || limiter[i] == '\"'))
			quote = limiter[i++];
		else if (quote && limiter[i] == quote)
			quote = 0;
		else
			aux = expand_lit(aux, limiter, &i);
	}
	return (aux);
}

// TODO: Quitar una (1) linea

char	*new_file(int *status)
{
	char	*tmp;
	char	*name;
	int		i;

	i = 0;
	while (i <= INT_MAX)
	{
		tmp = ft_itoa(i);
		if (!tmp)
		{
			*status = 1;
			return (NULL);
		}
		name = ft_strjoin("/tmp/heredoc", tmp);
		free(tmp);
		if (!name)
		{
			*status = 1;
			return (NULL);
		}
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

char	*create_tmp_file(char *limiter, int *status, int *fd, char **name)
{
	char	*limit;

	*name = new_file(status);
	if (!*name)
		return (NULL);
	*fd = open(*name, O_CREAT | O_EXCL | O_WRONLY, 0666);
	if (!*fd)
	{
		free(*name);
		*status = 1;
		return (NULL);
	}
	limit = remove_quotes(limiter);
	if (!limit)
	{
		unlink(*name);
		free(*name);
		*status = 1;
		return (NULL);
	}
	return (limit);
}
