#include "../../minishell.h"

static int	relative_path_checker(char *possible_path, t_env *env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*current_path;
	char	*new_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		return (1);
	}
	new_path = ft_strjoin(current_path, possible_path);
	if (chdir(new_path) == 0)
	{
		pwd = env_node_search("PWD", env);
		oldpwd = env_node_search("OLDPWD", env);
		if (path_update_control(pwd, oldpwd, new_path, &env) == 1)
			return (error_pointer_free(current_path, new_path, NULL, 2));
	}
		printf("cambiando ruta");
	pointer_free(current_path, new_path, NULL, 2);
	return (0);
}

static int	absolute_path_checker(char *possible_path, t_env *env)
{
	t_env	*pwd;
	t_env	*oldpwd;

	if (access(possible_path, X_OK) && access(possible_path, F_OK) == -1)
	{
		printf("no tengo permisos");
		return (1);
	}
	else
	{
		pwd = env_node_search("PWD", env);
		oldpwd = env_node_search("OLDPWD", env);
		if (path_update_control(pwd, oldpwd, possible_path, &env) == 1)
			return (1);
		chdir(possible_path);
	}
	return (0);
}

int ft_cd(char **cmd, t_env *env)
{
	char	**check_path;

	check_path = ft_split(cmd[1], ' ');
	if (check_path[0][1] == '/')
	{
		if (absolute_path_checker(check_path[0], env) == 1)
			return (1);
		else
			return (0);
	}
	if (check_path[0][1] != '.')
	{
		if (relative_path_checker(check_path[0], env) == 1)
			return (1);
		else
			return (0);
	}
		return (1);
}