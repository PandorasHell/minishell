#include "../../minishell.h"

int path_updater(char *key, char *value, t_env *env)
{
	t_env	*tmp_node;

	tmp_node = env_node_search(key, env);
	if (!tmp_node)
		return (1);
	free(tmp_node->content->value);
	tmp_node->content->value = ft_substr(value, \
		0, ft_strlen(value));
	if (!tmp_node->content->value)
		return (1);
	return (0);
}

int	path_update_control(t_env *pwd, t_env *oldpwd,\
			char *possible_path, t_env **env)
{
		if (oldpwd)
		{
			if (path_updater("OLDPWD", pwd->content->value, *env) == 1)
				return (1);
			if (path_updater("PWD", possible_path, *env) == 1)
				return (1);
		}
		else if (pwd)
		{
			if (path_updater("PWD", possible_path, *env) == 1)
				return (1);
		}
	return (0);
}
