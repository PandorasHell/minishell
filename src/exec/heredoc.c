#include "../../minishell.h"

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

t_cmd_red	*heredoc_cmd(t_cmd_red *redir, t_env *env, int *status)
{
	t_cmd_red	*tmp;
	t_cmd_red	*new;

	tmp = redir;
	while (tmp)
	{
		new = ft_calloc(1, sizeof(t_cmd_red));
		if (!new)
		{
			// hay que hacer tambien un unlink para eliminar los creados en caso de error
			free_cmd(redir);
			return (NULL);
		}
		new->content = ft_calloc(1, sizeof(t_cmd_dred));
		if (!redir->content)
		{
			// hay que hacer tambien un unlink para eliminar los creados en caso de error
			free(new);
			free_cmd(redir);
			return (NULL);
		}
		if (new->content->type == HEREDOC)
			status = resolve_heredoc(redir->content->where, env);
		else
			new->content->where = ft_strdup(redir->content->where);
		if (!new->content->where)
			return (free(new), 1);
		new->content->type = redir->content->type;
		ft_lstadd_back((t_list **)&new, (t_list *)new->content);
		tmp = tmp->next;
	}
	return (new);
}

int	create_heredocs(t_cmd *cmd, t_env *env)
{
	t_cmd		*tmp;
	t_cmd_red	*redir;
	int		status;

	tmp = cmd;
	status = 0;
	redir = NULL;	
	while (tmp)
	{
		if (tmp->info->redir)
			redir = heredoc_cmd(cmd->info->redir, env, &status);
		if (status)
			return (status);
		free_redir(tmp->info->redir);
		ft_lstadd_back((t_list **)&cmd->info->redir, (t_list *)redir);
		tmp = tmp->next;
	}
	return (status);
}