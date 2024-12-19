/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:32:57 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:32:58 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	variable_updater(char **cmd_matrix, t_env **env)
{
	t_env	*tmp_node;

	tmp_node = env_node_search(cmd_matrix[0], *env);
	free(tmp_node->content->value);
	if (cmd_matrix[1])
	{
		tmp_node->content->value = ft_substr(cmd_matrix[1], 0,
				ft_strlen(cmd_matrix[1]));
		if (!tmp_node->content->value)
			return (1);
	}
	return (0);
}

int	save_node_env(char **cmd_matrix, t_env *env)
{
	t_denv	*data;
	t_env	*node;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (1);
	data = malloc(sizeof(t_denv));
	if (!data)
		return (1);
	data->key = ft_strdup(cmd_matrix[0]);
	if (!data->key)
		return (error_pointer_free(data, NULL, NULL, 1));
	if (!cmd_matrix[1])
		data->value = ft_calloc(sizeof(char), 1);
	else
	{
		data->value = ft_strdup(cmd_matrix[1]);
		if (!data->value)
			return (error_pointer_free(data->key, data, NULL, 2));
	}
	node->content = data;
	ft_lstadd_back((t_list **)&env, (t_list *)node);
	return (0);
}

static char	***matrix_creator(char **cmd, t_cmd_name *exported_env, t_env *env)
{
	char	***cmd_matrix;
	int		i;
	int		j;

	j = 0;
	i = 0;
	cmd_matrix = ft_calloc(matrix_counter(cmd) + 1, sizeof(char **));
	if (!cmd_matrix)
		exit(1);
	while (cmd[++j])
	{
		if (cmd_checker(cmd[j]))
		{
			if (ft_strchr(cmd[j], '='))
			{
				cmd_matrix[i] = ft_split(cmd[j], '=');
				i++;
			}
			else
				export_foo_creator(cmd[j], exported_env, env);
		}
		else
			printf("export: %s: not a valid identifier\n", cmd[j]);
	}
	return (cmd_matrix);
}

static int	var_checker(char ***cmd_matrix, t_env *env, t_cmd_name *export_env)
{
	int			i;
	int			counter;
	t_cmd_name	*tmp;

	i = -1;
	while (cmd_matrix[++i])
	{
		if (env_node_search(cmd_matrix[i][0], env))
		{
			if (variable_updater(cmd_matrix[i], &env))
				return (1);
		}
		else
		{
			if (save_node_env(cmd_matrix[i], env))
				return (1);
		}
		tmp = exp_node_search(cmd_matrix[i][0], &counter, export_env);
		if (tmp && env_node_search(cmd_matrix[i][0], env))
			exp_node_control(tmp, export_env, counter);
	}
	return (0);
}

int	ft_export(char **cmd, t_env *env, t_cmd_name *exported_env)
{
	char	***cmd_matrix;
	int		cmd_counter;

	cmd_counter = matrix_counter(cmd);
	if (cmd_counter == 1)
		export_env(exported_env, env);
	cmd_matrix = matrix_creator(cmd, exported_env, env);
	if (!cmd_matrix)
		return (1);
	if (var_checker(cmd_matrix, env, exported_env))
	{
		free_matrix(cmd_matrix);
		return (1);
	}
	free_matrix(cmd_matrix);
	return (0);
}
