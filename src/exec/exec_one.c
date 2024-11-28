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
		perror("Error: execve failed");
		exit(1);
	}
}

static void	execute_cmd(t_cmd *cmd, t_env *env, t_cmd_red *redir)
{
	pid_t	pid;
	int		status;
    char	**cmd_matrix;
    char	**emv_matrix;

    cmd_matrix = cmd_to_array(cmd->info->word);
    emv_matrix = env_to_array(env);
	pid = fork();
	status = 0;
    if (!cmd_matrix || !emv_matrix)
    {
        perror("Error: malloc failed");
		exit(1);
    }
	if (pid < 0)
	{
		perror("Error: fork failed");
		return;
	}
	if (pid == 0)
	{
		manage_redir(redir);
		if (ft_is_builtin_checker(cmd_matrix, env))
			exit(0);
		child_process(cmd_matrix, emv_matrix);
	}
	else
		waitpid(pid, &status, 0);
	cleanup(cmd_matrix);
    cleanup(emv_matrix);
}

void	execute_one(t_cmd *cmd, t_env *env)
{
	// TODO: Pasar lo de si es un builtin a la ejecucion de los hijos
    // if (is_built_in(args[0]))
    //     execute_built_in(args, env);
	// #TODO: Añadir señales en la ejecucion.
    execute_cmd(cmd, env, cmd->info->redir);
}
