#include "../../minishell.h"

static void	execute_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid < 0)
	{
		perror("Error: fork failed");
		return ;
	}
	if (pid == 0)
	{
		manage_redir(cmd->info->redir);
		child_process(cmd, env);
	}
	else
		waitpid(pid, &status, 0);
}

void	execute_one(t_cmd *cmd, t_env *env)
{
	if (ft_is_builtin(cmd->info->word->name))
		exec_builtin(cmd, env);
	else
		execute_cmd(cmd, env);
}
