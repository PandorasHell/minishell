#include "../../minishell.h"

static int flag_checker(char **cmd, int i)
{
	int j;

	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] == '-')
		{
			while (cmd[i][j] == 'n')
			{
				j++;
			if (cmd[i][j] != 'n' && cmd[i][j] != '\0')
				return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void ft_echo(char **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (cmd[j])
		j++;
	i = flag_checker(cmd, i);
	printf("%d < j\n", j);
	printf("%d < i\n", i);
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
}