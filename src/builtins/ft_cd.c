#include "../../minishell.h"

static int send_to_home(t_env *env)
{
	t_env *home;

	home = env_node_search("HOME", env);
	if (!home)
		return (1);
	chdir(home->content->value);
	return (0);
}

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
	new_path = append_path(current_path, possible_path);
	printf("the new path is: %s\n", new_path);
	if (chdir(new_path) == 0)
	{
		printf("hola1");
		pwd = env_node_search("PWD", env);
		oldpwd = env_node_search("OLDPWD", env);
		if (path_update_control(pwd, oldpwd, new_path, &env) == 1)
			return (error_pointer_free(current_path, new_path, NULL, 2));
	}
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

static int	cd_path_control(char **check_path, t_env *env)
{
		if (check_path[0][0] == '/')
		{
			if (absolute_path_checker(check_path[0], env) == 1)
				return (1);
			return (0);
		}
		if (check_path[0][0] != '.')
		{
			if (relative_path_checker(check_path[0], env) == 1)
				return (1);
			return (0);
		}
		if (check_path[0][0] == '.')
		{
			
		}
}

int ft_cd(char **cmd, t_env *env)
{
	char	**check_path;
	int		flag;

	flag = matrix_counter(cmd);
	if (flag > 1)
	{
		check_path = ft_split(cmd[1], ' ');
	}
	return (send_to_home(env));
}