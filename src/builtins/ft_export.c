#include "../../minishell.h"

int	variable_updater(char **cmd_matrix, t_env **env)
{
	t_env	*tmp_node;
	int		cmd_counter;

	cmd_counter = matrix_counter(cmd_matrix);
	if (cmd_counter > 2)
	{
		tmp_node = env_node_search(cmd_matrix[0], *env);
		free(tmp_node->content->value);
		tmp_node->content->value = ft_substr(cmd_matrix[1], 0,
				ft_strlen(cmd_matrix[1]));
		if (!tmp_node->content->value)
			return (1);
	}
	return (0);
}

static int	save_node_env(char **cmd_matrix, t_env *env)
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

static char	***matrix_creator(char **cmd, t_cmd_name *exported_env)
{
	char	***cmd_matrix;
	int		i;
	int		j;

	i = 0;
	j = 1;
	i = matrix_counter(cmd);
	cmd_matrix = ft_calloc(i + 1, sizeof(char **));
	if (!cmd_matrix)
		return (NULL);
	i = 0;
	while (cmd[j])
	{
		if (ft_strchr(cmd[j], '='))
		{
			cmd_matrix[i] = ft_split(cmd[j], '=');
			if (!cmd_matrix[i])
			{
				free_matrix(cmd_matrix);
				return (NULL);
			}
		}
		else
			export_foo_creator(exported_env, cmd[j]);
		i++;
		j++;
	}
	return (cmd_matrix);
}

static int	var_checker(char ***cmd_matrix, t_env **env)
{
	int	i;

	i = 0;
	while (cmd_matrix[i])
	{
		if (env_node_search(cmd_matrix[i][0], *env))
		{
			if (variable_updater(cmd_matrix[i], env))
				return (1);
		}
		else
		{
			if (save_node_env(cmd_matrix[i], *env))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **cmd, t_env *env, t_cmd_name *exported_env)
{
	char				***cmd_matrix;
	int					cmd_counter;
	
	cmd_counter = matrix_counter(cmd);
	if (cmd_counter == 1)	
		export_env(exported_env, env);
	cmd_matrix = matrix_creator(cmd, exported_env);
	if (!cmd_matrix)
		return (1);
	if (var_checker(cmd_matrix, &env))
	{
		free_matrix(cmd_matrix);
		return (1);
	}
	free_matrix(cmd_matrix);
	return (0);
}
