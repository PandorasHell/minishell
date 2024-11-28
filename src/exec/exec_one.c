#include "../../minishell.h"

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
		free(path);
		perror("Error: execve failed");
		exit(1);
	}
}

// static void	execute_cmd(char **args, char **envp, t_cmd_red *redir)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	status = 0;
// 	if (pid < 0)
// 	{
// 		perror("Error: fork failed");
// 		return;
// 	}
// 	if (pid == 0)
// 	{
// 		manage_redir(redir);
// 		child_process(args, envp);
// 	}
// 	else
// 		waitpid(pid, &status, 0);
// }

void	execute_one(t_cmd *cmd, t_env *env)
{
    char	**args;
    char	**envp;
 	pid_t	pid;
	int		status;

    args = cmd_to_array(cmd->info->word);
    envp = env_to_array(env);
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
		child_process(args, envp);
	}
	else
		waitpid(pid, &status, 0);
	// TODO: Pasar lo de si es un builtin a la ejecucion de los hijos
    // if (is_built_in(args[0]))
    //     execute_built_in(args, env);
	// #TODO: Añadir señales en la ejecucion.
    //execute_cmd(args, envp, cmd->info->redir);
	cleanup(args);
    cleanup(envp);
}
