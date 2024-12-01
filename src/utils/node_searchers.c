#include "../../minishell.h"

t_env *unset_node_search(char *key, int *j, t_env *env)
{
	t_env *tmp;

	tmp = env;
	if (!key || !env)
		return (NULL);
	if (ft_strcmp(tmp->content->key, key) == 0)
		return (tmp);
	while(tmp)
	{
		(*j)++;
		if (ft_strcmp(tmp->next->content->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env *env_node_search(char *key, t_env *env)
{
	t_env *tmp;

	tmp = env;
	if (!key || !env)
		return (NULL);
	while(tmp != NULL)
	{
		if (ft_strcmp(tmp->content->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
