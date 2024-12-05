#include "../../minishell.h"

static void	print_without_flag(char **cmd, int *i, int j)
{
		while ((*i) < j)
		{
			if (cmd[(*i) + 1] == NULL)
				printf("%s\n", cmd[(*i)]);
			else
				printf("%s ", cmd[(*i)]);
			(*i)++;
		}
}

static void	print_with_flag(char **cmd, int *i, int j)
{
		while ((*i) < j)
		{
			if (cmd[(*i) + 1] == NULL)
				printf("%s", cmd[(*i)]);
			else
				printf("%s ", cmd[(*i)]);
			(*i)++;
		}
}

static int	flag_checker(char **cmd, int iterator)
{
	int	j;

	while (cmd[iterator])
	{
		j = 1;
		if (cmd[iterator][0] == '-')
		{
			while (cmd[iterator][j])
			{
				if (cmd[iterator][j] != 'n' && cmd[iterator][j] != '\0')
					return (iterator);
				j++;
			}
		}
		else
			return (iterator);
		iterator++;
	}
	return (iterator);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (cmd[j])
		j++;
	i = flag_checker(cmd, i);
	if (i > 1)
		print_with_flag(cmd, &i, j);
	else
		print_without_flag(cmd, &i, j);
	return (0);
}
