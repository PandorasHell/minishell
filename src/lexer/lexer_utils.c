#include "../../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}
