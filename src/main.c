#include "../minishell.h"
#include "../lib/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **enviroment)
{
	char	*line;
	t_lenv	*env;
	t_lword	*cmd;
	(void)argc;
	(void)argv;

	env = save_env(enviroment);
	if (env)
		printf("Aaª\n");
		
	while (1)
	{
		line = readline("minishell $>> ");
		if (line)
		{
			cmd = lexical_analysis(line);
			while (cmd)
			{
				printf("<%s>\n", cmd->word);
				cmd = cmd->next;
			}
			if (*line != '\0')
				add_history(line);
		}
		else
			break ;
	}
	//rl_clear_history();
	return (0);
}


