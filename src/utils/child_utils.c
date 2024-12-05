#include "../../minishell.h"

pid_t	child_birth(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror(strerror(errno));
		return (1);
	}
	return (pid);
}

int	pipe_builder(int fd_mid[2])
{
	if (pipe(fd_mid) < 0)
	{
		perror(strerror(errno));
		return (1);
	}
	return (0);
}

static int	first_part(int (*fd)[2], int fd_mid[2], t_cmd *cmd, t_env *env)
{
	if (close(fd[1][0]) < 0)
	{
		perror(strerror(errno));
		ft_exit(NULL, cmd, env);
	}
	if (dup2(fd[0][0], STDIN_FILENO) < 1)
	{
		perror(strerror(errno));
		ft_exit(NULL, cmd, env);
	}
	if (close(fd[0][0]) < 1)
	{
		perror(strerror(errno));
		ft_exit(NULL, cmd, env);
	}
	if (close(fd_mid[0]) < 1)
	{
		perror(strerror(errno));
		ft_exit(NULL, cmd, env);
	}
	return (0);
}

void	child_labour(int (*fd)[2], int fd_mid[2], t_cmd *cmd, t_env *env)
{
	first_part(fd, fd_mid, cmd, env);
	if (dup2(fd_mid[1], STDOUT_FILENO) < 0)
	{
		perror(strerror(errno));
		ft_exit(NULL, cmd, env);
	}
	if (close(fd_mid[1]) < 0)
	{
		perror(strerror(errno));
		ft_exit(NULL, cmd, env);
	}
	if (manage_redir(cmd->info->redir))
		ft_exit(NULL, cmd, env);
	if (ft_is_builtin(cmd->info->word->name))
	{
		exec_builtin(cmd, env);
		ft_exit(NULL, cmd, env);
	}
	child_process(cmd, env);
}
