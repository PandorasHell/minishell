#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_handler = 0;

int	exit_line(char *line)
{
	while (*line)
	{
		if (*line == '<')
		{
			if (*(line + 1) == '<')
				return (0);
		}
		line++;
	}
	return (1);
}

static void	exec_line(t_cmd *cmd, t_env *env, char *line, 
					t_cmd_name *export_env)
{
	t_lexer	*lexer;
	t_cmd	*parser;

	lexer = NULL;
	parser = NULL;
	lexer = lexical_analysis(line);
	if (lexer == NULL)
		return ;
	parser = complete_parser(lexer);
	cmd = expand_cmd(parser, env);
	free_lexer(&lexer);
	free_cmd(parser);
	ft_lstclear((t_list **)&parser, free);
	exec_cmd(cmd, env, export_env);
	if (cmd != NULL)
	{
		free_cmd(cmd);
		ft_lstclear((t_list **)&cmd, free);
	}
}

static void	line_reader(t_cmd *cmd, char *line, t_env *env,
			 t_cmd_name *export_env)
{
    main_signals();
	while (1)
	{
		g_handler = 0;
		rl_catch_signals = 0;
		line = readline("minishell $>> ");
		main_signals();
		if (!line)
			exit(0);
		if (line)
		{
			if (ft_strlen(line) == 0)
			{
				free(line);
				continue ;
			}
			exec_line(cmd, env, line, export_env);
			if (!check_character_for_history(line[0]) && exit_line(line))
				add_history(line);
			free(line);
		}
	}
}

int	main(int argc, char **argv, char **enviroment)
{
	char		*line;
	t_env		*env;
	t_cmd		*cmd;
	t_cmd_name	*export_env;

	export_env = ft_calloc(1, sizeof(t_cmd_name));
	(void)argc;
	(void)argv;
	env = save_env(enviroment);
	cmd = NULL;
	line = NULL;
	line_reader(cmd, line, env, export_env);
	rl_clear_history();
	ft_lstclear((t_list **)&export_env, free);
	free(export_env);
	return (0);
}
