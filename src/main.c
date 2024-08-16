#include "../minishell.h"
#include "../lib/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_env	*save_env(char **env)
{
	t_env	*lst;
	t_env	*tmp;
	t_env	*last;
	int		i;

	i = 0;
	lst = NULL;
	last = NULL;
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		if (!tmp)
		{
			perror("Error creating env list");
			ft_lstclear((t_list **)&lst, free);
			return (NULL);
		}
		tmp->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		tmp->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		tmp->next = NULL;
		if (!lst)
		{
			lst = tmp;
			last = tmp;
		}
		else
		{
			last->next = tmp;
			last = tmp;
		}
		i++;
	}
	return (lst);
}

int main(int argc, char **argv, char **enviroment)
{
	//char	*line;
	t_env	*env;
	(void)argc;
	(void)argv;

	env = save_env(enviroment);
	while (env)
	{
		printf("key: %s\n", env->key);
		printf("value: %s\n", env->value);
		env = env->next;
	}
	
	
	// while (1)
	// {
	// 	line = readline("minishell $>> ");
	// 	if (line)
	// 	{
	// 		add_history(line);
	// 	}
	// 	else
	// 		break ;
	// }
	// rl_clear_history();
	return (0);
}