#include "../../minishell.h"

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	if (create_heredoc(cmd, env))
		return ;
	if (!cmd->info->word)
	{
		if (cmd->info->redir)
		{
			if (cmd->info->redir->content->type == HEREDOC)
				unlink(cmd->info->redir->content->where);
			else
				perror("Error: No such file or directory");
		}
		free_cmd(cmd);
		return ;
	}
	if (ft_lstsize((t_list *)cmd) == 1)
		execute_one(cmd, env);
	else
		execute_n(cmd, env);
}
