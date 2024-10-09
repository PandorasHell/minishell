#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


static void line_reader(t_lexer *lexer, t_cmd *cmd, char *line, t_env *env)
{
	t_cmd	*parser = NULL;
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
			parser = complete_parser(lexer);
			cmd = expand_cmd(parser, env);
			free_lexer(&lexer);
			if (cmd != NULL)
			{
				free_cmd(cmd);
				ft_lstclear((t_list **)&cmd, free);
			}
			free_cmd(parser);
			ft_lstclear((t_list **)&parser, free);
			if (!check_character_for_history(line[0]))
				add_history(line);
			free(line);
		}
		else
			break ;
	}
}

int main(int argc, char **argv, char **enviroment)
{
	char	*line;
	t_env	*env;
	t_lexer	*lexer;
	t_cmd	*cmd;
	(void)argc;
	(void)argv;

	env = save_env(enviroment);
	if (env)
		printf("Aaª\n");
	lexer = NULL;
	cmd = NULL;
	line = NULL;
	line_reader(lexer, cmd, line, env);
	//rl_clear_history();
	free_env(env);
	return (0);
}