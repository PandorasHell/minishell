#include "../../minishell.h"

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

static void	execute_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid < 0)
	{
		perror("Error: fork failed");
		return;
	}
	if (pid == 0)
	{
		manage_redir(cmd->info->redir);
		child_process(cmd, env);
	}
	else
		waitpid(pid, &status, 0);
}

void	execute_one(t_cmd *cmd, t_env *env)
{
// TODO: Pasar lo de si es un builtin a la ejecucion de los hijos
	// #TODO: Añadir señales en la ejecucion.
	if (ft_is_builtin(cmd->info->word->name))
		exec_builtin(cmd, env);
	else
		execute_cmd(cmd, env);
}
