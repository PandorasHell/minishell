#include "../../minishell.h"

//TODO:hacer la funcion cd.
//static int check_cd(t_cmd *cmd)
//{
//	this function should be able to know where the user is and send him to where he wants to be
//	with either the relative or the absolute path.
//}

static int check_pwd_env(t_cmd *cmd)
{

}

int built_in_command_checker(t_cmd *cmd, t_denv *env)
{
	int compared;
	int comparer;
	int command_size;

	compared = 0;
	comparer = 0;
	command_size = ft_strlen(cmd->info->word);
//	if (command_size == 2)
//	{
//		if (check_cd(cmd))
//			return (2);
//	}
	if (command_size == 3)
	{
		if (check_pwd_env(cmd))
			return (3);
	}
	if (command_size == 4)
	{
		if (check_echo_exit(cmd))
			return (4);
	}
	if (command_size == 5)
	{
		if (check_export_unset(cmd))
			return (5);
	}
	return (0);
}