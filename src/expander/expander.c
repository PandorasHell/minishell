#include "../../minishell.h"

char	*expand_exit_code(char *ret, int *i)
{
	char	*tmp;

	tmp = ft_itoa(127);
	ret = ft_strappend(ret, tmp);
	if (!ret)
	{
		free(tmp);
		return(NULL);
	}
	free(tmp);
	(*i)++;
	return (ret);
}

char	*expand_env(char *ret, char *name, int *i, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->content->key, &name[*i],
				ft_strlen(env->content->key) + 1) == 0)
		{
			ret = ft_strappend(ret, env->content->value);
			if (!ret)
				return (NULL);
			*i += ft_strlen(env->content->key);
			break ;
		}
		else if (env->next == NULL)
			break ;
		env = env->next;
	}
	return (ret);
}

char	*expand_value(char *name, t_env *env)
{
	char	*ret;
	char	lit[2];
	int		i;

	i = 0;
	ret = NULL;
	while (name[i])
	{
		if (name[i] == '$')
		{
			i++;
			if (name[i] == '?')
				ret = expand_exit_code(ret, &i);
			else
				ret = expand_env(ret, name, &i, env);
		}
		else
		{
			lit[0] = name[i++];
			lit[1] = '\0';
			ret = ft_strappend(ret, lit);
		}
		if(!ret)
			break ;
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
		tmp = set_cmd_mem();
		if (!tmp)
		{
			ft_lstclear((t_list **)&cmd, free);
			return (NULL);
		}
		if (expand_name(tmp, env, cmd) || expand_redir(tmp, env, cmd))
			return (NULL);
		ft_lstadd_back((t_list **)&exp, (t_list *)tmp);
		cmd = cmd->next;
	}
	free_cmd(cmd);
	return (exp);
}
