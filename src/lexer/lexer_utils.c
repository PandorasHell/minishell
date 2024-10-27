#include "../../minishell.h"

/**
 * @brief Check if the character is a space character
 * @param c The character to check
 * @return 1 if the character is a space character, 0 otherwise
 */

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/**
 * @brief Check if the character is an operator character
 * @param c The character to check
 * @return 1 if the character is an operator character, 0 otherwise
 */

int	is_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

/**
 * @brief Check if the character is a quote character
 * @param c The character to check
 * @return 1 if the character is a quote character, 0 otherwise
 */

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
