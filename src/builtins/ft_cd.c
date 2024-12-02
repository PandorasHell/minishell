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


static int	path_checker(char *possible_path, t_env *env)
{
	char	*current_path;
	char	*new_path;

	current_path = getcwd(NULL, 0);
	new_path = NULL;
	if (!current_path)
		return (1);
	if (possible_path[0] != '/' && possible_path[0] != '.')
		new_path = append_path(current_path, possible_path);
	if (new_path)
	{
		if (chdir(new_path) == 0)
		{
			if (path_var_updater(new_path, current_path, env) == 1)
				return (error_pointer_free(new_path, current_path, NULL, 2));
		}
		return (pointer_free(current_path, new_path, NULL, 2));
	}
	if (chdir(possible_path) == 0)
	{
		if (possible_path[0] == '.')
			//TODO: como manejar la entrada a dicha funcion.
		if (path_var_updater(new_path, current_path, env) == 1)
			return (error_pointer_free(current_path, NULL, NULL, 1));
	}
	return (pointer_free(current_path, new_path, NULL, 2));
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