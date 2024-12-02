#include "../../minishell.h"

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int	status;
	char	**aux;

	status = 0;
	aux = cmd_to_array(cmd->info->word);
	if (ft_strcmp(aux[0], "echo") == 0)
		status = ft_echo(aux);
	if (ft_strcmp(aux[0], "pwd") == 0)
		status = ft_pwd();
	if (ft_strcmp(aux[0], "env") == 0)
		status = ft_env(env);
	if (ft_strcmp(aux[0], "export") == 0)
		status = ft_export(aux, env);
	if (ft_strcmp(aux[0], "unset") == 0)
		status = ft_unset(aux, env);
	if (ft_strcmp(aux[0], "cd") == 0)
		status = ft_cd(aux, env);
	cleanup(aux);
	return (status);
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}