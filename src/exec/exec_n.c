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

static void	child_process(char **cmd, char **envp)
{
	char	*path;

	if (relative_path(cmd, &path) == 0)
	{
		if (cmd[0])
			path = get_path(cmd[0], envp);
	}
	if (!path)
	{
		perror("Error: command not found");
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("Error: execve failed");
		exit(1);
	}
}

static pid_t	ft_first_cmd(int (*fd)[2], t_cmd_name *name, t_env *env, t_cmd_red *redir)
{
	pid_t	pid_in;
	char	**args;
    char	**envp;

    args = cmd_to_array(name);
    envp = env_to_array(env);
	pid_in = fork();
	if (pid_in < 0)
		return (0);
	if (pid_in == 0)
	{
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][0]);
        manage_redir(redir);
		child_process(args, envp);
	}
	close(fd[0][1]);
	cleanup(args);
    cleanup(envp);
	return (pid_in);
}

static pid_t	ft_mid_cmd(int (*fd)[2], t_cmd_name *name, t_env *env, t_cmd_red *redir)
{
	pid_t	pid_mid;
	int		fd_mid[2];
	char	**args;
    char	**envp;

    args = cmd_to_array(name);
    envp = env_to_array(env);
	if (pipe(fd_mid) < 0)
		return (0);
	pid_mid = fork();
	if (pid_mid < 0)
		return (0);
	if (pid_mid == 0)
	{
		close(fd[1][0]);
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd_mid[0]);
		dup2(fd_mid[1], STDOUT_FILENO);
		close(fd_mid[1]);
		manage_redir(redir);
		child_process(args, envp);
	}
	close(fd[0][0]);
	close(fd_mid[1]);
	cleanup(args);
    cleanup(envp);
	fd[0][0] = fd_mid[0];
	return (pid_mid);
}

static pid_t	ft_last_cmd(int (*fd)[2],  t_cmd_name *name, t_env *env, t_cmd_red *redir)
{
	pid_t	pid_out;
	char	**args;
    char	**envp;

    args = cmd_to_array(name);
    envp = env_to_array(env);

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
		manage_redir(redir);
		child_process(args, envp);
	}
	cleanup(args);
    cleanup(envp);
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
	child[i++] = ft_first_cmd(fd, cmd->info->word, env, cmd->info->redir);
	cmd = cmd->next;
	while (cmd->next != NULL)
	{
		child[i++] = ft_mid_cmd(fd, cmd->info->word, env, cmd->info->redir);
		cmd = cmd->next;
	}
	child[i++] = ft_last_cmd(fd, cmd->info->word, env, cmd->info->redir);
	ft_waitchild(child, i);
	free(child);
	// TODO: Pasar lo de si es un builtin a la ejecucion de los hijos
    // if (is_built_in(args[0]))
    //     execute_built_in(args, env);
	// #TODO: Añadir señales en la ejecucion.

}
