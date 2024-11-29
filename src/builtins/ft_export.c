#include "../../minishell.h"

static int variable_updater(char **cmd_matrix, t_env *env)
{
	t_env	*tmp_node;

	tmp_node = pwd_finder(cmd_matrix[0], env);
	free(tmp_node->content->value);
	tmp_node->content->value = ft_substr(cmd_matrix[1], 0, ft_strlen(cmd_matrix[1]));
	if (!tmp_node->content->value)
		return (1);
	return (0);
}

static int	save_node_env(char **cmd_matrix, t_env *env)
{
	t_denv	*data;

	data = (t_denv *)malloc(sizeof(t_denv));
	if (!data)
		return (1);
	data->key = ft_strdup(cmd_matrix[0]);
	if (!data->key)
	{
		free(data);
		return (1);
	}
	data->value = ft_strdup(cmd_matrix[1]);
	if (!data->value)
	{
		free(data->key);
		free(data);
		return (1);
	}
	ft_lstadd_back((t_list **)&env, (t_list *)data);
	return (0);
}

static char ***matrix_creator(char **cmd)
{
	char	***cmd_matrix;
	int		i;
	int		j;

	i = 0;
	j = 1;
	i = matrix_counter(cmd);
	cmd_matrix = ft_calloc( i + 1,sizeof(char **));
	if (!cmd_matrix)
		return (NULL);
	i = 0;
	while (cmd[j])
	{
		cmd_matrix[i] = ft_split(cmd[j], '=');
		if (!cmd_matrix[i])
		{
			free_matrix(cmd_matrix);
			return (NULL);
		}
		i++;
		j++;
	}
	return (cmd_matrix);
}

static int	var_checker(char ***cmd_matrix, t_env *env)
{
	int		i;

	i = 0;
	while (cmd_matrix[i])
	{
		if (pwd_finder(cmd_matrix[i][0], env))
		{
			if (variable_updater(cmd_matrix[i], env))
				return (1);
		}
		else
		{
			if (save_node_env(cmd_matrix[i], env))
				return (1);
		}
		i++;
	}
	return (0);
}

int ft_export(char **cmd, t_env *env)
{
	char	***cmd_matrix;

	cmd_matrix = matrix_creator(cmd);
	if (!cmd_matrix)
		return (-1);
	if (var_checker(cmd_matrix, env))
	{
		free_matrix(cmd_matrix);
		return (1);
	}
	free_matrix(cmd_matrix);
	t_env *tmp = pwd_finder("PWD", env);
	printf("key is : %s and value is : %s\n",tmp->content->key, tmp->content->value);
	return (0);
}

