#include "../../minishell.h"

static int	ft_exit_arg_checker(char *str)
{
	int	checker;

	checker = 0;
	if (str == NULL)
		return (1);
	while (str[checker] != '\0')
	{
		if (!ft_isdigit(str[checker]))
			return (1);
		checker++;
	}
	return (0);
}

int	ft_exit(char **cmd_matrix, t_cmd *cmd, t_env *env)
{
	if (cmd_matrix)
	{
		if (matrix_counter(cmd_matrix) > 2)
		{
			ft_putstr_fd("Only use 1 numeric argument\n", 2);
			return (1);
		}
		if (cmd_matrix[1])
		{
			if (ft_exit_arg_checker(cmd_matrix[1]) == 1)
			{
				ft_putstr_fd("Only use numeric values\n", 2);
				return (1);
			}
			cleanup(cmd_matrix);
			free_cmd(cmd);
			ft_lstclear((t_list **)&cmd, free);
			free_env(&env);
			exit(1);
		}
	}
	cleanup(cmd_matrix);
	free_cmd(cmd);
	ft_lstclear((t_list **)&cmd, free);
	free_env(&env);
	exit(1);
}
