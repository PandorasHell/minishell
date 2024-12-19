/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:33:14 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:33:15 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	error_args(void)
{
	ft_putstr_fd("too many arguments\n", 2);
	return (1);
}

static int	send_to_home(char *old_path, t_env *env)
{
	t_env	*home;

	home = env_node_search("HOME", env);
	if (!home)
	{
		ft_putstr_fd("Error: there is no HOME\n", 2);
		return (1);
	}
	chdir(home->content->value);
	if (path_update_control(old_path, env))
		return (1);
	return (0);
}

static int	path_updater(char *key, char *value, t_env *env)
{
	t_env	*tmp_node;

	tmp_node = env_node_search(key, env);
	if (tmp_node)
	{
		free(tmp_node->content->value);
		tmp_node->content->value = NULL;
	}
	if (value)
	{
		tmp_node->content->value = ft_substr(value, 0, ft_strlen(value));
		if (!tmp_node->content->value)
			return (1);
	}
	return (0);
}

int	path_update_control(char *old_path, t_env *env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*new_path;

	new_path = getcwd(NULL, 0);
	pwd = env_node_search("PWD", env);
	oldpwd = env_node_search("OLDPWD", env);
	if (pwd)
	{
		if (path_updater("PWD", new_path, env) == 1)
		{
			free(new_path);
			return (1);
		}
	}
	if (oldpwd)
	{
		if (path_updater("OLDPWD", old_path, env) == 1)
		{
			free(new_path);
			return (1);
		}
	}
	free(new_path);
	return (0);
}

int	ft_cd(char **cmd, t_env *env)
{
	char	*current_path;
	int		flag;

	if (matrix_counter(cmd) > 2)
		return (error_args());
	current_path = getcwd(NULL, 0);
	flag = matrix_counter(cmd);
	if (flag > 1)
	{
		if (chdir(cmd[1]) == -1)
		{
			ft_putendl_fd(strerror(errno), 1);
			free(current_path);
			return (1);
		}
		path_update_control(current_path, env);
		free(current_path);
		return (0);
	}
	if (send_to_home(current_path, env))
	{
		free(current_path);
		return (1);
	}
	return (0);
}
