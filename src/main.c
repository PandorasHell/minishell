#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int control_tower(t_cmd *cmd, char *line, t_env *env)
{
    t_lexer *lexer;
    t_cmd   *parser;

	lexer = NULL;
	parser = NULL;
	lexer = lexical_analysis(line);
	if (!lexer)
		return (1);
    parser = complete_parser(lexer);
	if (!parser)
		return (1);
    cmd = expand_cmd(parser, env);
	if (!cmd)
        free_lexer(&lexer);
    if (cmd != NULL)
    {
        free_cmd(cmd);
        ft_lstclear((t_list **)&cmd, free);
    }
    free_cmd(parser);
    ft_lstclear((t_list **)&parser, free);
}


static void line_reader(t_lexer *lexer, t_cmd *cmd, char *line, t_env *env)
{
	while (1)
	{
		line = readline("minishell $>> ");
        //TODO: manejar enter en "line" y EOF(se;ales)
		if (line)
		{
			if (!exit_checker(line, "exit"))
			{
				free(line);
				break ;
			}
			control_tower(cmd, env);
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
	//TODO:manejar el mensaje de error de env
	if (!env)
		return (1);
	lexer = NULL;
	cmd = NULL;
	line = NULL;
	line_reader(lexer, cmd, line, env);
	//rl_clear_history();
	free_env(env);
	return (0);
}


