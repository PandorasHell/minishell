/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:12:06 by smeixoei          #+#    #+#             */
/*   Updated: 2024/07/11 15:44:46 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*c_path;
	char	**e_path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (!(*env) || ft_strncmp(*env, "PATH=", 5) != 0)
	{
		if (!(*env))
			ft_error("Error: PATH not found");
		env++;
	}
	e_path = ((i = 0), ft_split(env[i] + 5, ':'));
	while (e_path[i])
	{
		c_path = ((path = ft_strjoin(e_path[i], "/")), ft_strjoin(path, cmd));
		if (path)
			free(path);
		if (access(c_path, X_OK) == 0)
			return (c_path);
		free(c_path);
		i++;
	}
	return (NULL);
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
			ft_error("Error: command not found");
	}
	return (check);
}

void	ft_execute(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	if (!*argv)
		ft_error("Error: invalid argument");
	path = NULL;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_error("Error: split");
	if (ft_relative_path(cmd, &path) == 0)
	{
		if (cmd[0])
			path = ft_get_path(cmd[0], env);
	}
	if (path && execve(path, cmd, env) == -1)
	{
		free(path);
		ft_error("Error: execve failed");
	}
}
