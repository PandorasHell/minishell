#include "../../minishell.h"

void	save_data_env(t_lenv *tmp, char **env, int i)
{
	t_denv *data;

	data = (t_denv *)malloc(sizeof(t_denv));
	if (!data)
		return ;
	tmp->content = data;
	data->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
	data->value = ft_strdup(ft_strchr(env[i], '=') + 1);
}

t_lenv	*save_env(char **env)
{
	t_lenv	*lst;
	t_lenv	*tmp;
	int		i;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_lenv));
		if (!tmp)
		{
			perror("Error creating env list");
			ft_lstclear((t_list **)&lst, free);
			return (NULL);
		}
		save_data_env(tmp, env, i);
		ft_lstadd_back((t_list **)&lst, (t_list *)tmp);
		i++;
	}
	return (lst);
}
