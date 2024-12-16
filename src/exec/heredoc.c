#include "../../minishell.h"

static void	expand_line_heredoc(char *line, t_env *env, int tmp_fd)
{
	char	*expanded_line;

	expanded_line = NULL;
	expanded_line = expand_dolar_heredoc(line, env);
	if (expanded_line)
	{
		write(tmp_fd, expanded_line, ft_strlen(expanded_line));
		write(tmp_fd, "\n", 1);
		free(expanded_line);
	}
}

char	*heredoc(char *limiter, t_env *env, int *status)
{
	int		tmp_fd;
	char	*line;
	char	*limit;
	char	*here_doc;

	limit = create_tmp_file(limiter, status, &tmp_fd, &here_doc);
	if (!limit)
		return (NULL);
	main_signals();
	while (1)
	{
		line = get_next_line(1);
		if (!line && g_handler == SIGINT)
			break ;
		if (!ft_strcmp(line, limit))
		{
			free(line);
			free(limit);
			break ;
		}
		expand_line_heredoc(line, env, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	return (here_doc);
}

static t_cmd_red	*set_redir_mem(t_cmd_red *redir, int *status)
{
	t_cmd_red	*new;

	new = ft_calloc(1, sizeof(t_cmd_red));
	if (!new)
	{
		free_redir(redir);
		*status = 1;
		return (NULL);
	}
	new->content = ft_calloc(1, sizeof(t_cmd_dred));
	if (!new->content)
	{
		free(new);
		free_redir(redir);
		*status = 1;
		return (NULL);
	}
	return (new);
}

t_cmd_red	*heredoc_cmd(t_cmd_red *redir, t_env *env, int *status)
{
	t_cmd_red	*tmp;
	t_cmd_red	*new;
	t_cmd_red	*aux;

	aux = ((tmp = redir), NULL);
	while (tmp)
	{
		new = set_redir_mem(aux, status);
		if (!new)
			return (NULL);
		if (tmp->content->type == HEREDOC)
			new->content->where = heredoc(tmp->content->where, env, status);
		else
			new->content->where = ft_strdup(tmp->content->where);
		if (!new->content->where)
		{
			free(new->content);
			free_redir(redir);
			return ((*status = 1), NULL);
		}
		new->content->type = tmp->content->type;
		ft_lstadd_back((t_list **)&aux, (t_list *)new);
		tmp = tmp->next;
	}
	return (aux);
}

int	create_heredoc(t_cmd *cmd, t_env *env)
{
	t_cmd_red	*redir;
	int			status;

	if (!cmd || !env)
		return (1);
	status = 0;
	while (cmd)
	{
		redir = NULL;
		if (cmd->info && cmd->info->redir)
			redir = heredoc_cmd(cmd->info->redir, env, &status);
		if (status)
			return (status);
		free_redir(cmd->info->redir);
		cmd->info->redir = redir;
		cmd = cmd->next;
	}
	return (status);
}
