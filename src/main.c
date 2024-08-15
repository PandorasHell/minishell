#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **enviroment)
{
	char	*line;
	(void)argc;
	(void)argv;

	// Guardar enviroment para utilizarlo dentro de minishell.
	while (1)
	{
		line = readline("minishell $>> ");
		if (line)
		{
			add_history(line);
		}
		else
			break ;
	}
	rl_clear_history();
	return (0);
}