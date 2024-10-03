#include "../../minishell.h"

char	*expand_exit_code(char *ret, int *i)
{
	char	*tmp;

	tmp = ft_itoa(127);
	ret = ft_strappend(ret, tmp);
	free(tmp);
	(*i)++;
	return (ret);
}

char	*expand_env(char *ret, char *name, int *i, t_env *env)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (env)
	{
		if (ft_strncmp(env->content->key, &name[*i],
			ft_strlen(env->content->key) + 1) == 0)
		{
			tmp = ft_strdup(env->content->value);
			ret = ft_strappend(ret, tmp);
			*i += ft_strlen(env->content->key);
			break;
		}
		else if(env->next == NULL){
			ret = NULL;
		}
		env = env->next;
	}
	return (ret);
}

char	*expand_value(char *name, t_env *env)
{
	char 	*ret;
	char	lit[2];
	int		i;

	i = 0;
	ret = ft_strdup("");
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
		expand_name(tmp, env, cmd);
		if (tmp->info->word)
			printf("name: %s\n", tmp->info->word->name);
		expand_redir(tmp, env, cmd);
		if (tmp->info->redir)
			printf("redir: %s\n", tmp->info->redir->content->where);
		ft_lstadd_back((t_list **)&exp, (t_list *)tmp);
		cmd = cmd->next;
	}
	return (exp);
}
