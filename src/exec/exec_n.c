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

void	child_process(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;
	char	**args;

	args = cmd_to_array(cmd->info->word);
	envp = env_to_array(env);
	path = NULL;
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
	child_signals();
	if (path)
        printf("%s\n", path);
	if (execve(path, args, envp) == -1)
	{
		// free(path);
		// cleanup(args);
		// cleanup(envp);
		perror("Error");
		exit(1);
	}
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
	ignored_signals();
	ft_waitchild(child, i);
	free(child);
}
