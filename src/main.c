#include "../minishell.h"
#include "../lib/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **enviroment)
{
	char	*line;
	t_lenv	*env;
	t_lexer	*lexer;
	t_cmd	*cmd;
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
			if (!exit_checker(line, "exit"))
			{
				free(line);
				break ;
			}
			lexer = lexical_analysis(line);
			cmd = final_cmd(lexer);
			free_lexer(&lexer);
			if (cmd != NULL)
			{
				free_cmd(cmd);
				ft_lstclear((t_list **)&cmd, free);
			}
			if (*line != '\0')
				add_history(line);
			free(line);
		}
		else
			break ;
	}
	rl_clear_history();
	free_env(env);
	return (0);
}


