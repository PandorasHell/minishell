/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:12:06 by smeixoei          #+#    #+#             */
/*   Updated: 2024/08/06 18:59:58 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_search_path(char *cmd, char **e_path)
{
	int		i;
	char	*path;
	char	*c_path;

	i = 0;
	while (e_path[i])
	{
		path = ft_strjoin(e_path[i], "/");
		if (path)
		{
			c_path = ft_strjoin(path, cmd);
			free(path);
			if (c_path)
			{
				if (access(c_path, X_OK) == 0)
					return (c_path);
				free(c_path);
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_get_path(char *cmd, char **env)
{
	char	*c_path;
	char	**e_path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (!(*env) || ft_strncmp(*env, "PATH=", 5) != 0)
	{
		if (!(*env))
			ft_error("Error: path not found", NULL);
		env++;
	}
	e_path = ft_split(env[0] + 5, ':');
	if (!e_path)
		ft_error("Error: split", NULL);
	c_path = ft_search_path(cmd, e_path);
	ft_free_split(e_path);
	return (c_path);
}

int	ft_relative_path(char **cmd, char **path)
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
		else
			ft_error("Error: file not found", NULL);
	}
	return (check);
}

void	ft_execute(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	if (!*argv)
		ft_error("Error: command not found", NULL);
	path = NULL;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_error("Error: split", NULL);
	if (ft_relative_path(cmd, &path) == 0)
	{
		if (cmd[0])
			path = ft_get_path(cmd[0], env);
	}
	if (!path || execve(path, cmd, env) == -1)
		ft_error("Error: execve failed", NULL);
	ft_free_split(cmd);
}
