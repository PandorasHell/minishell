#include "../../minishell.h"


void built_in_env(t_lenv *env)
{
	while (env)
	{
		if (!ft_strncmp(env->content->key, "PWD", 3))
		{
			printf("%s\n",env->content->value);
			return ;
		}
		env = env->next;
	}
}