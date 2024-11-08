#include "../../minishell.h"

char    *cmd_to_args(t_cmd *cmd)
{
    t_cmd_name	*tmp;
    char		*args;

    tmp = cmd->info->word;
	args = ft_strdup("");
    while (tmp)
    {
        args = ft_strappend(args, tmp->name);
		args = ft_strappend(args, " ");
        if (!args)
		{
			free(args);
			return (NULL);
		}
        tmp = tmp->next;
    }
    return (args);
}

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	i = ft_lstsize((t_list *)env);
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->content->key);
		envp[i] = ft_strappend(envp[i], "=");
		envp[i] = ft_strappend(envp[i], tmp->content->value);
		if (!envp[i])
		{
			cleanup(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (envp);
}

char	*search_path(char *cmd, char **e_path)
{
	int		i;
	char	*path;
	char	*c_path;

	i = 0;
	while (e_path[i])
	{
		path = ft_strappend(e_path[i], "/");
		if (path)
		{
			c_path = ft_strappend(path, cmd);
			printf("c_path: %s\n", c_path);
			// #TODO: conseguir que furule el access.
			if (access(c_path, X_OK) == 0)
				return (c_path);
			free(c_path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*c_path;
	char	**e_path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (!(*env) || ft_strncmp(*env, "PATH=", 5) != 0)
	{
		if (!(*env))
			printf("Error: path not found\n");
		env++;
	}
	e_path = ft_split(env[0] + 5, ':');
	if (!e_path)
		printf("Error: split\n");
	c_path = search_path(cmd, e_path);
	free(e_path);
	return (c_path);
}

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
	if (pid == 0)
	{
		path = get_path(args, envp);
		cmd = ft_split(args, ' ');
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

    args = cmd_to_args(cmd);
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
