#include "../../minishell.h"

void	execute_cmd(char *args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**cmd;

	pid = fork();
	status = 0;
	if (pid < 0)
	{
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}
    // #TODO: gestionar redirecciones antes de ejecutar.
	if (pid == 0)
	{
		cmd = ft_split(args, ' ');
		if (relative_path(cmd, &path) == 0)
		{
			if (cmd[0])
				path = get_path(cmd[0], envp);
		}
		if (!path || execve(path, cmd, envp) == -1)
		{
			cleanup(cmd);
			free(path);
			printf("Error: %s\n", strerror(errno));
			exit (1); ;
		}
	}
	else
		waitpid(pid, &status, 0);
}

void	execute_one(t_cmd *cmd, t_env *env)
{
    char	*args;
    char	**envp;

    args = cmd_to_array(cmd);
    envp = env_to_array(env);
    if (!args || !envp)
    {
        printf("Error: malloc failed\n");
        return ;
    }
	
    // if (is_built_in(args[0]))
    //     execute_built_in(args, env);
    execute_cmd(args, envp);
	free(args);
    cleanup(envp);
}
