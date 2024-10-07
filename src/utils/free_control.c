#include "../../minishell.h"

int free_control_redir(t_cmd_red *node1, t_cmd_dred *node2, int i)
{
	if (i == 1)
		free_cmd((t_cmd *) node1);
	else if (i == 2)
	{
		free_cmd((t_cmd *) node1);
		free_cmd((t_cmd *) node2);
	}
	return (1);
}

int free_control_name(t_cmd_name *node1)
{
	free_cmd((t_cmd *) node1);
	return (1);
}