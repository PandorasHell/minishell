#include "../../minishell.h"

static int	flag_checker(char **cmd, int i)
{
	int	j;

	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] == '-')
		{
			while (cmd[i][j])
			{
				if (cmd[i][j] != 'n' && cmd[i][j] != '\0')
					return (i);
				j++;
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
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
	{
		while (i < j)
		{
			if (cmd[i + 1] == NULL)
				printf("%s", cmd[i]);
			else
				printf("%s ", cmd[i]);
			i++;
		}
	}
	else
	{
		while (i < j)
		{
			if (cmd[i + 1] == NULL)
				printf("%s\n", cmd[i]);
			else
				printf("%s ", cmd[i]);
			i++;
		}
	}
	return (0);
}
