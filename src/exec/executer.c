#include "../../minishell.h"

void	exec_cmd(t_cmd *cmd, t_env *env, t_cmd_name *export_env)
{
	if (create_heredoc(cmd, env))
		return ;
	if (!cmd->info->word)
	{
		if (cmd->info->redir)
			manage_only_redir_line(cmd->info->redir);
		free_cmd(cmd);
		return ;
	}
	if (ft_lstsize((t_list *)cmd) == 1)
		execute_one(cmd, env, export_env);
	else
		execute_n(cmd, env);
}
