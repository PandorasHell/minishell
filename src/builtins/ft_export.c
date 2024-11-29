#include "../../minishell.h"

static int variable_updater(char *command, t_env *env)
{
	t_env	*tmp_node;

	tmp_node = pwd_finder(command, env);
	free(tmp_node->content->value);
	tmp_node->content->value = ft_substr(command, 0, ft_strlen(command));
	if (!tmp_node->content->value)
		return (1);
	return (0);
}

static t_denv	*save_node_env(char **command)
{
	t_denv	*data;

	data = (t_denv *)malloc(sizeof(t_denv));
	if (!data)
		return (NULL);
	data->key = ft_strdup(command[0]);
	if (!data->key)
	{
		free(data);
		return (NULL);
	}
	data->value = ft_strdup(command[1]);
	if (!data->value)
	{
		free(data->key);
		free(data);
		return (NULL);
	}
	return (data);
}

int ft_export(char **cmd, t_env *env)
{
	t_env	*tmp2;

	if (pwd_finder(cmd[0], env))
	{
		if (variable_updater(cmd[1], env))
			return (1);
	}
	tmp2 = (t_env *)malloc(sizeof(t_env));
    if (!tmp2)
    {
    	return (1);
    }
	tmp2->content = save_node_env(cmd);
    if (!tmp2->content)
    {
    	free(tmp2);
    	return (1);
    }
	else
		ft_lstadd_back((t_list **)&env, (t_list *)tmp2);
    return (0);
}

