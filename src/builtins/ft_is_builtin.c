#include "../../minishell.h"

static int builtins_second_part(char **cmd, t_env *env)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(cmd, env);
		return (1);
	}
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export(cmd, env);
		return (1);
	}
	if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(cmd, env);
		return (1);
	}
	return (0);
}

static int builtins_first_part(char **cmd, t_env *env)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(cmd);
		return (1);
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(env);
		return (1);
	}
	return (0);
}

int	ft_is_builtin_checker(char **cmd, t_env *env)
{
	if (builtins_first_part(cmd, env))
		return (1);
	if (builtins_second_part(cmd, env))
		return (1);
	return (0);
}