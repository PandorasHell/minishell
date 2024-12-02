#include "../../minishell.h"

static int path_updater(char *key, char *value, t_env *env)
{
	t_env	*tmp_node;

	tmp_node = env_node_search(key, env);
	free(tmp_node->content->value);
	tmp_node->content->value = ft_substr(value, \
		0, ft_strlen(value));
	if (!tmp_node->content->value)
		return (1);
	return (0);
}


// TODO: crear la funcion que manejara y actualizara el directorio final si es un path absoluto.
// int absolute_path(char *path, char *old_path, t_env *env)
// {
//
// }

int	path_var_updater(char *path, char *old_path, t_env *env)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = env_node_search("PWD", env);
	oldpwd = env_node_search("OLDPWD", env);
	if (pwd)
	{
		if (path_updater("PWD", path, env) == 1)
			return (1);
	}
	if (oldpwd)
	{
		if (path_updater("OLDPWD", old_path, env) == 1)
			return (1);
	}
	return (0);
}
