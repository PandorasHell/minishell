#include "../../minishell.h"

/**
 * @brief this function verifies if the line contains only exit
 * followed by the allowed white spaces in shell and nothing else.
 * @return return 1 in the event of it finding a character that
 * isnt allowed, and 0 if the exit command is allowed.
 */

int	exit_checker(const char *line, const char *comparer)
{
	int	i;

	i = 0;
	while (comparer[i] && line[i])
	{
		if (line[i] != comparer[i])
			return (1);
		i++;
	}
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r'
			&& line[i] != '\n' && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}
