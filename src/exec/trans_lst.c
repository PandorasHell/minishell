#include "../../minishell.h"

char    *cmd_to_array(t_cmd *cmd)
{
    t_cmd_name	*tmp;
    char		*args;

    tmp = cmd->info->word;
	args = ft_strdup("");
    while (tmp)
    {
        args = ft_strappend(args, tmp->name);
		args = ft_strappend(args, " ");
        if (!args)
		{
			free(args);
			return (NULL);
		}
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
