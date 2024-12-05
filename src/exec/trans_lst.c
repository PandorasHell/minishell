#include "../../minishell.h"

char	**cmd_to_array(t_cmd_name *cmd)
{
	t_cmd_name	*tmp;
	char		**args;
	int			i;

	i = ft_lstsize((t_list *)cmd);
	args = ft_calloc(i + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	tmp = cmd;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->name);
		if (!args[i])
		{
			cleanup(args);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (args);
}

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	i = ft_lstsize((t_list *)env);
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->content->key);
		envp[i] = ft_strappend(envp[i], "=");
		envp[i] = ft_strappend(envp[i], tmp->content->value);
		if (!envp[i])
		{
			cleanup(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (envp);
}
