#include "../../minishell.h"

int	cmd_checker(char *cmd)
{
	if (ft_isalpha(cmd[0]) || cmd[0] == '_')
	{
		return (1);
	}
	return (0);
}

void	exp_node_control(t_cmd_name *node, t_cmd_name *export_env, int counter)
{
	t_cmd_name	*tmp_node2;

	tmp_node2 = export_env;
	if (node && counter == 0)
	{
		free_exp_first_node(tmp_node2);
	}
	else if (node && counter > 0)
	{
		free_exp_mid_node(tmp_node2);
	}
}

t_cmd_name	*exp_node_search(char *cmd, int *node_counter,
		t_cmd_name *export_env)
{
	t_cmd_name	*tmp;

	tmp = export_env;
	if (!cmd || !export_env)
		return (NULL);
	if (ft_strcmp(cmd, tmp->name) == 0)
	{
		return (tmp);
	}
	while (tmp != NULL)
	{
		if (node_counter)
			(*node_counter)++;
		if (ft_strcmp(tmp->name, cmd) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	export_foo_creator(char *cmd, t_cmd_name *exported_env, t_env *env)
{
	t_cmd_name	*node;
	t_env		*tmp;

	node = exp_node_search(cmd, NULL, exported_env);
	if (node)
		return ;
	tmp = env_node_search(cmd, env);
	if (tmp)
		return ;
	node = ft_calloc(1, sizeof(t_cmd_name));
	if (!node)
		exit(1);
	node->name = ft_substr(cmd, 0, ft_strlen(cmd));
	if (!node->name)
		exit(1);
	ft_lstadd_back((t_list **)&exported_env, (t_list *)node);
}

void	export_env(t_cmd_name *exported_env, t_env *env)
{
	t_env		*tmp;
	t_cmd_name	*tmp2;

	tmp = env;
	if (!tmp)
		exit(1);
	while (tmp)
	{
		if (tmp->content->value)
			printf("declare -x %s=%s\n", tmp->content->key,
				tmp->content->value);
		tmp = tmp->next;
	}
	tmp2 = exported_env;
	while (tmp2)
	{
		if (tmp2->name)
			printf("declare -x %s\n", tmp2->name);
		tmp2 = tmp2->next;
	}
}
