#include "../../minishell.h"

static void	clean_up_for_exit(char **cmd_matrix, t_cmd *cmd, \
			t_env *env, int exit_status)
{
	cleanup(cmd_matrix);
	free_cmd(cmd);
	ft_lstclear((t_list **)&cmd, free);
	free_env(&env);
	exit(exit_status);
}

static int	ft_exit_arg_checker(char *str)
{
	int	checker;
	long result;

	result = ft_atol(str);
	checker = 0;
	if (str == NULL)
		return (1);
	while (str[checker] != '\0')
	{
		if (!ft_isdigit(str[checker]))
			return (1);
		checker++;
	}
	result = ft_atol(str);
	if (result < INT_MIN || result > INT_MAX)
		return (1);
	return (0);
}

int	ft_exit(char **cmd_matrix, t_cmd *cmd, t_env *env)
{
	int	exit_status;
	unsigned int randomizer;

	if (g_handler == SIGQUIT)
		exit_status = g_handler;
	if (cmd_matrix)
	{
		if (matrix_counter(cmd_matrix) > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		if (cmd_matrix[1])
		{
			if (ft_exit_arg_checker(cmd_matrix[1]) == 1)
			{
				ft_putstr_fd("Only use numeric values\n", 2);
				clean_up_for_exit(cmd_matrix, cmd, env, 2);
			}
			randomizer = ft_atoi(cmd_matrix[1]);
		}
		clean_up_for_exit(cmd_matrix, cmd, env, randomizer);
	}
	clean_up_for_exit(cmd_matrix, cmd, env, exit_status);
	return (0);
}
