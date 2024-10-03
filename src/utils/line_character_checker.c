#include "../../minishell.h"

int	check_character_for_history(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}
