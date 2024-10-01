#include "../../minishell.h"

char	*expand_value(char *name, t_env *env)
{
	char 	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (name[i])
	{
		if (name[i] == '$')
		{
			i++;
			if (name[i] == '?')
			{
				ret = ft_itoa(127);
				j += ft_strlen(ret);
				return (ret);
			}
			else
			{
				while (env)
				{
					if (ft_strncmp(env->content->key, &name[i], ft_strlen(env->content->key)) == 0)
					{
						ret = ft_strjoin(ret, env->content->value);
						j += ft_strlen(env->content->value);
						break;
					}
					env = env->next;
				}
			}
		}
		else
			ret[j++] = name[i];
		i++;
		}
	return (ret);
}


t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*exp;
	t_cmd	*tmp;

	exp = NULL;
	while (cmd)
	{
		tmp = set_cmd_mem(cmd);
		if (!tmp)
			return (ft_lstclear((t_list **)&cmd, free), NULL);
		expand_name(tmp->info->word, env, cmd);
		expand_redir(tmp->info->redir, env, cmd);
		ft_lstadd_back((t_list **)&exp, (t_list *)tmp);
		cmd = cmd->next;
	}
	return (exp);
}
