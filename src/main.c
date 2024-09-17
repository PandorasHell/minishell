#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

//TODO: hay que agregar aca la entrada al ejecutor.
static int line_parser(t_lexer *lexer, t_cmd *cmd, char *line)
{
	lexer = lexical_analysis(line);
	if (!lexer)
		return (free(line), 1);
	cmd = final_cmd(lexer);
	if (!cmd)
		return (free_lexer(&lexer), free(line), 1);
	free_lexer(&lexer);
	if (cmd != NULL)
	{
		free_cmd(cmd);
		ft_lstclear((t_list **)&cmd, free);
	}
	if (!check_character_for_history(line[0]))
		add_history(line);
	free(line);
	return (0);
}

static void line_reader(t_lenv *env, t_lexer *lexer, t_cmd *cmd, char *line)
{
	while (1)
	{
		line = readline("minishell $>> ");
		if (line)
		{
			if (line[0] == 'L')
				built_in_env(env);
			if (!exit_checker(line))
			{
				free(line);
				return ;
			}
			built_in_command_checker(cmd, env);
			if (line_parser(lexer, cmd, line))
				break ;
		}
		else
			break ;
	}
}

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
	lexer = NULL;
	cmd = NULL;
	line = NULL;
	line_reader(env, lexer, cmd, line);
	rl_clear_history();
	free_env(env);
	return (0);
}


