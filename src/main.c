#include "../minishell.h"
#include "../lib/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **enviroment)
{
	char	*line;
	t_lenv	*env;
	t_lexer	*lexer;
	//t_cmd	*cmd;
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
			lexer = lexical_analysis(line);
			//cmd = final_cmd(lexer);
			while (lexer)
			{
				printf("<%d %s>\n", lexer->content->key, lexer->content->value);
				lexer = lexer->next;
			}
			if (!ft_strncmp(line, "exit", 4))
				break ;
			if (*line != '\0')
				add_history(line);
		}
		else
			break ;
	}
	rl_clear_history();
	return (0);
}


