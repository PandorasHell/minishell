#include "../../minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	while (tmp)
	{
		printf("%s=%s\n", tmp->content->key, tmp->content->value);
		tmp = tmp->next;
	}
	return (0);
}
