#include "../../minishell.h"

static int	manage_infile(char *where, int *in, int type)
{
	int	fd;

	if (*in)
		close(*in);
	fd = open(where, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: open failed");
		return (1);
	}
	*in = fd;
	if (type == HEREDOC)
		unlink(where);
	return (0);
}

static int	manage_outfile(char *where, int *out, int type)
{
	int	fd;

	if (*out)
		close(*out);
	if (type == APPEND)
		fd = open(where, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(where, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error: open failed");
		return (1);
	}
	*out = fd;
	return (0);
}

static int	dup_process(int in, int out)
{
	if (in)
	{
		if (dup2(in, STDIN_FILENO) < 0)
		{
			perror(strerror(errno));
			return (1);
		}
		close(in);
	}
	if (out)
	{
		if (dup2(out, STDOUT_FILENO) < 0)
		{
			perror(strerror(errno));
			return (1);
		}
		close(out);
	}
	return (0);
}

int	manage_redir(t_cmd_red *redir)
{
	int			in;
	int			out;
	t_cmd_red	*tmp;

	in = 0;
	out = 0;
	tmp = redir;
	while (tmp)
	{
		if (tmp->content->type == INFILE || tmp->content->type == HEREDOC)
		{
			if (manage_infile(tmp->content->where, &in, tmp->content->type))
				return (1);
		}
		else if (tmp->content->type == OUTFILE || tmp->content->type == APPEND)
		{
			if (manage_outfile(tmp->content->where, &out, tmp->content->type))
				return (1);
		}
		tmp = tmp->next;
	}
	if (dup_process(in, out))
		return (1);
	return (0);
}
