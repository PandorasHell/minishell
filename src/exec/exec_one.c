#include "../../minishell.h"

static void	execute_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	child_signals();
	pid = fork();
	status = 0;
	if (pid < 0)
	{
		perror("Error");
		return ;
	}
	if (pid == 0)
	{
		manage_redir(cmd->info->redir);
		child_process(cmd, env);
	}
	waitpid(pid, &status, 0);
	main_signals();
}

void	execute_one(t_cmd *cmd, t_env *env,
					 t_cmd_name *export_env)
{
	if (ft_is_builtin(cmd->info->word->name))
		exec_builtin(cmd, env, export_env);
	else
		execute_cmd(cmd, env);
}
