#include "../../minishell.h"

static int send_to_home(t_env *env)
{
	t_env *home;

	home = env_node_search("HOME", env);
	if (!home)
	{
		ft_putstr_fd("Error: there is no HOME\n", 2);
		return (1);
	}
	chdir(home->content->value);
	return (0);
}

static int changing_parent_dir(char *path, char *old_path, t_env *env)
{
	char *current_dir;

	current_dir = NULL;
	if (path[0] == '.' && path[1] == '.')
	{
		if (chdir(path) == 0)
		{
			current_dir = getcwd(NULL, 0);
			if (!current_dir)
				return (1);
			if (path_var_updater(current_dir, old_path, env) == 1)
			{
				free(current_dir);
				return (1);
			}
			free(current_dir);
			return (0);
		}
		strerror(errno);
		return (1);
	}
	return (-1);
}

static int cd_relative_path(char *current_path, char * possible_path, t_env *env)
{
	char	*new_path;


	new_path = NULL;
	if (possible_path[0] != '/' || (possible_path[0] == '.' && possible_path[1] != '.'))
	{
		new_path = append_path(current_path, possible_path);
		if (chdir(new_path) == 0)
		{
			if (path_var_updater(new_path, current_path, env) == 1)
			{
				free(new_path);
				return (1);
			}
			free(new_path);
			return (0);
		}
		free(new_path);
		return (1);
	}
	return (-1);
}

static int	path_checker(char *possible_path, t_env *env)
{
	char	*current_path;
	int		status;

	current_path = getcwd(NULL, 0);
	if (!current_path)
		return (1);
	status = changing_parent_dir(possible_path, current_path, env);
	if (status != -1)
	{
		free(current_path);
		if (status == 1)
			return (1);
		return (0);
	}
	status = cd_relative_path(current_path, possible_path,  env);
	if (status != -1)
	{
		free(current_path);
		if (status == 1)
			return (1);
		return (0);
	}
return (0);

	// if (chdir(possible_path) == 0)
	// {
	// 	printf ("%s\n", possible_path);
	// 	if (possible_path[0] == '.')
	// 		return (changing_parent_dir(possible_path, current_path, env));
	// 	if (path_var_updater(new_path, current_path, env) == 1)
	// 		return (error_pointer_free(current_path, NULL, NULL, 1));
	// }
	// return (pointer_free(current_path, new_path, NULL, 2));
}

int ft_cd(char **cmd, t_env *env)
{
	int		flag;

	flag = matrix_counter(cmd);
	if (flag > 1)
	{
		if (flag > 2)
		{
			perror("too many arguments");
			return (1);
		}
		if (path_checker(cmd[1], env) == 1)
			return (1);
		return (0);
	}
	return (send_to_home(env));
}