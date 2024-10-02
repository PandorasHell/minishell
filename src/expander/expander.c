#include "../../minishell.h"

char	*expand_value(char *name, t_env *env)
{
	char 	*ret;
	char 	*temp;
	int		flag = 1;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (name[i])
	{
		if (name[i] == '$')
		{
			i++;
			flag = 1;
			if (name[i] == '?')
			{
				temp = ft_itoa(127);
				ret = ft_strappend(ret, temp);
				free(temp);
				i++;
			}
			else
			{
				while (env)
				{
					if (ft_strncmp(env->content->key, &name[i], ft_strlen(env->content->key)) == 0) // Solucionar esto
					{
						temp = ft_strdup(env->content->value);
						ret = ft_strappend(ret, temp);
						free(temp);
						i += ft_strlen(env->content->key);
						break;
					}
					env = env->next;
				}
			}
		}
		else
		{
			if (flag)			
			{
				ret = ft_strappend(ret, &name[i]);
				flag = 0;
			}
			i++;
		}
	}
	printf("ret final: %s\n", ret);
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
