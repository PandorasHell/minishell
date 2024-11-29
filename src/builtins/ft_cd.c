#include "../../minishell.h"

/*
static int make_pwd(t_env *env)
{
	t_env *tmp_home;
	t_env *tmp_path;

	tmp_home = NULL;
	tmp_path = NULL;
	tmp_home = pwd_finder("HOME", env);
	if (!tmp_home)
		return (1);
	tmp_path = pwd_finder("PATH", env);
	if (!tmp_path)
		return (1);

}

int ft_cd(t_cmd *cmd, t_env *env)
{
	int i;
	int arguments;
	char **commands;


	arguments = 0;
	commands = ft_split(cmd->info->word->name, ' ');
	i = 0;
	while (commands[arguments])
		arguments++;
	if (arguments == 1 && ft_strncmp(commands[0], "cd", 2) == 0)
		make_pwd_home(env);
	while(path[i] != '/' || path[i] != '.')
		i++;


		return (1);
}*/