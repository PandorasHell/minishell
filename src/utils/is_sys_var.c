#include "../../minishell.h"

int	is_sys_var(char *name, int *pos)
{
	int	i;

	i = (*pos);
	if (name[i] == '_' || ft_isalpha(name[i]) || name[i] == '?')
		i++;
	else
		return (0);
	while (name[i] && name[i] != ' ' && name[i] != '=' && name[i] != '/')
	{
		if (ft_strchr("_-?=/.@!^+%*#&()[]{}<>|;:,.~`'\"\\", name[i])
			|| ft_isalpha(name[i]) || ft_isdigit(name[i]))
		{
			i++;
			if (name[i] == '\"')
				break ;
		}
		else
			return (0);
	}
	return (1);
}
