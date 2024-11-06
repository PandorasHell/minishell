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

int	resolve_heredoc(char *limiter, t_env *env)
{
	// ahora mismo esto es una copia del heredoc de pipex
	// Hay que  expandir las variables de entorno dentro del documento T_T
	char	*line;
	int		tmp_fd;
	char 	*here_doc;
	
	here_doc = create_tmp_file(); // Generar el archivo temporal para almacenar el archivo
	tmp_fd = open(here_doc, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_fd < 0)
		ft_error("Error: open", &tmp_fd);
	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(here_doc, O_RDONLY);
	if (tmp_fd < 0 || unlink(here_doc) < 0)
		ft_error("Error: open or unlink", &tmp_fd);
	return (tmp_fd);
}

t_cmd_red	*set_redir_mem(t_cmd_red *redir, int *status)
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

	tmp = redir;
	aux = NULL;
	while (tmp)
	{
		new = set_redir_mem(aux, status);
		if (!new)
			return (NULL);
		if (new->content->type == HEREDOC)
			*status = resolve_heredoc(redir->content->where, env);
		else
			new->content->where = ft_strdup(redir->content->where);
		if (!new->content->where)
		{
			free(new->content);
			free_redir(redir);
			*status = 1;
			return (NULL);
		}
		new->content->type = redir->content->type;
		ft_lstadd_back((t_list **)&aux, (t_list *)new);
		tmp = tmp->next;
	}
	return (aux);
}

int	create_heredocs(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;
	t_cmd_red	*redir;
	int		status;

	if (!cmd || !env)
		return (1);
	tmp = cmd;
	status = 0;
	redir = NULL;	
	while (tmp)
	{
		if (tmp->info && tmp->info->redir)
			redir = heredoc_cmd(tmp->info->redir, env, &status);
		if (status)
			return (status);
		free_redir(cmd->info->redir);
		cmd->info->redir = redir;
		tmp = tmp->next;
	}
	return (status);
}