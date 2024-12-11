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
		perror("Error");
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("Error");
		exit(1);
	}
}

void	execute_n(t_cmd *cmd, t_env *env)
{
	int		fd[2][2];
	pid_t	*child;
	int		i;

	ignored_signals();
	child = (pid_t *)malloc(sizeof(pid_t) * ft_lstsize((t_list *)cmd));
	if (!child)
		return ;
	if (pipe(fd[0]) < 0)
		return ;
	i = 0;
	child_signals();
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
	main_signals();
}
