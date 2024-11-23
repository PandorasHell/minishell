#include "../../minishell.h"

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	if (create_heredoc(cmd, env))
		return ;
	if (!cmd->info->word)
	{
		unlink(cmd->info->redir->content->where);
		free_cmd(cmd);
		return ;
	}
	//TODO: agregar ft_error colocando un perror.
	if (ft_lstsize((t_list *)cmd) == 1)
		execute_one(cmd, env);
	else
		execute_n(cmd, env);
}
