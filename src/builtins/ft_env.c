#include "../../minishell.h"

void ft_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf("%s=%s\n", tmp->content->key, \
			tmp->content->value);
		tmp = tmp->next;
	}
}