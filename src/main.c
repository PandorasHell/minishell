#include "../minishell.h"
#include "../lib/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **enviroment)
{
	char	*line;
	t_lenv	*env;
	(void)argc;
	(void)argv;

	env = save_env(enviroment);
	if (env)
		printf("Aaª\n");
	while (env)
	{
		printf("key: %s\n", env->content->key);
		printf("value: %s\n", env->content->value);
		env = env->next;
	}
		
	while (1)
	{
		line = readline("minishell $>> ");
		if (line)
		{
			//lexical_analysis(line);
			if (*line != '\0')
				add_history(line);
		}
		else
			break ;
	}
	rl_clear_history();
	return (0);
}