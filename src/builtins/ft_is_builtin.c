#include "../../minishell.h"

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int		status;
	char	**cmd_matrix;

	status = 0;
	cmd_matrix = cmd_to_array(cmd->info->word);
	if (ft_strcmp(cmd_matrix[0], "echo") == 0)
		status = ft_echo(cmd_matrix);
	if (ft_strcmp(cmd_matrix[0], "pwd") == 0)
		status = ft_pwd();
	if (ft_strcmp(cmd_matrix[0], "env") == 0)
		status = ft_env(env);
	if (ft_strcmp(cmd_matrix[0], "export") == 0)
		status = ft_export(cmd_matrix, env);
	if (ft_strcmp(cmd_matrix[0], "unset") == 0)
		status = ft_unset(cmd_matrix, env);
	if (ft_strcmp(cmd_matrix[0], "cd") == 0)
		status = ft_cd(cmd_matrix, env);
	if (ft_strcmp(cmd_matrix[0], "exit") == 0)
		status = ft_exit(cmd_matrix, cmd, env);
	cleanup(cmd_matrix);
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
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}