#include "../../minishell.h"

void	ft_waitchild(pid_t *child, int cmds)
{
	int		status;
	pid_t	wait;
	int		i;

	i = 0;
	while (i < cmds)
	{
		wait = waitpid(child[i], &status, 0);
		if (wait == -1)
			return ;
		i++;
	}
}

static void	child_process(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;
	char	**args;

	args = cmd_to_array(cmd->info->word);
    envp = env_to_array(env);
	if (relative_path(args, &path) == 0)
	{
		if (args[0])
			path = get_path(args[0], envp);
	}
	if (!path)
	{
		perror("Error: command not found");
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		free(path);
		cleanup(args);
		cleanup(envp);
		perror("Error: execve failed");
		exit(1);
	}
}

static pid_t	ft_first_cmd(int (*fd)[2], t_cmd *cmd, t_env *env)
{
	pid_t	pid_in;

	pid_in = fork();
	if (pid < 0)
	{
		perror("Error: fork failed");
		return;
	}
	if (pid_in == 0)
	{
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][0]);
		close(fd[1][1]);
        manage_redir(cmd->info->redir);
		child_process(cmd , env);
	}
	close(fd[0][1]);
	close(fd[1][1]);
	return (pid_in);
}

static pid_t	ft_mid_cmd(int (*fd)[2], t_cmd *cmd, t_env *env)
{
	pid_t	pid_mid;
	int		fd_mid[2];

	if (pipe(fd_mid) < 0)
	{
		perror("Error: pipe failed");
		return;
	}
	pid_mid = fork();
	if (pid_mid < 0)
	{
		perror("Error: fork failed");
		return;
	}
	if (pid_mid == 0)
	{
		close(fd[1][0]);
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd_mid[0]);
		dup2(fd_mid[1], STDOUT_FILENO);
		close(fd_mid[1]);
		manage_redir(cmd->info->redir);
		child_process(cmd , env);
	}
	close(fd[0][0]);
	close(fd_mid[1]);
	fd[0][0] = fd_mid[0];
	return (pid_mid);
}

static pid_t	ft_last_cmd(int (*fd)[2], t_cmd *cmd, t_env *env)
{
	pid_t	pid_out;

	pid_out = fork();
	if (pid_out < 0)
	{
		perror("Error: fork failed");
		return (0);
	}
	if (pid_out == 0)
	{
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd[1][1]);
		manage_redir(cmd->info->redir);
		child_process(cmd , env);
	}
	close(fd[0][0]);
	close(fd[1][1]);
	return (pid_out);
}

void	execute_n(t_cmd *cmd, t_env *env)
{
	int		fd[2][2];
	pid_t	*child;
	int		i;


	child = (pid_t *)malloc(sizeof(pid_t) * ft_lstsize((t_list *)cmd));
	if (!child)
		return ;
	if (pipe(fd[0]) < 0)
		return ;
	i = 0;
	child[i++] = ft_first_cmd(fd, cmd, env);
	cmd = cmd->next;
	while (cmd->next != NULL)
	{
		child[i++] = ft_mid_cmd(fd, cmd, env);
		cmd = cmd->next;
	}
	child[i++] = ft_last_cmd(fd, cmd, env);
	ft_waitchild(child, i);
	free(child);
}
