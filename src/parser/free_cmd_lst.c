#include "../../minishell.h"


void free_cmd_lst(t_cmd **cmd)
{
	t_cmd *temp;

	temp = (*cmd);
	while (temp)
	{
		(*cmd) = (*cmd)->next;
		free(temp->info);
		free(temp);
		temp = (*cmd);
	}
}