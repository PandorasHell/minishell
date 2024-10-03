#include "../../minishell.h"

/**
 * @brief this function checks if status say its PIPE if it is
 * it tries to advance the lexer if possible.
 * @param lexer the the list that contains the words to parse.
 * @param status it shows what value is being handled.
 * @return return 1 if status is PIPE or 0 if it isn't.
 */

int	status_pipe(t_lexer **lexer, int status)
{
	if (status == PIPE)
	{
		if ((*lexer)->next)
			(*lexer) = (*lexer)->next;
		return (1);
	}
	return (0);
}

/**
 * @brief this function checks if status is REDIR and if it is
 * it tries to advance the lexer if possible,
 * else it free's cmd and prints an error message.
 * @param lexer the list that contains the words to parse.
 * @param status it shows what value is being handled.
 * @return return 0 if status is REDIR or 1 if it isn't.
 */

int	status_redir(t_lexer **lexer, int status, t_cmd *cmd)
{
	if (status == REDIR)
	{
		if ((*lexer)->next)
			(*lexer) = (*lexer)->next;
		else
		{
			free_cmd(cmd);
			printf("NO REDIR ERROR \n");
			return (1);
		}
	}
	return (0);
}
