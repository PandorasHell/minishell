#include "../../minishell.h"

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
		{
			printf("Error: path not found\n");
			return (NULL);
		}
		env++;
	}
	e_path = ft_split(env[0] + 5, ':');
	if (!e_path)
		printf("Error: split\n");
	c_path = search_path(cmd, e_path);
	free(e_path);
	return (c_path);
}

int	relative_path(char **cmd, char **path)
{
	int	check;

	if (*cmd == NULL)
		return (0);
	check = 0;
	if (ft_strncmp(*cmd, "/", 1) == 0 || ft_strncmp(*cmd, "./", 2) == 0
		|| ft_strncmp(*cmd, "../", 2) == 0)
		check = 1;
	if (check == 1)
	{
		if (access(cmd[0], F_OK) == 0)
			*path = cmd[0];
	}
	return (check);
}
