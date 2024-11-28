#include "../../minishell.h"

static int	check_exp_env(char *name, int *i, t_env *env)
{
	if (ft_strncmp(env->content->key, &name[*i],
			ft_strlen(env->content->key)) == 0
		&& (name[*i + ft_strlen(env->content->key)] == '\0'
			|| name[*i + ft_strlen(env->content->key)] == ' '
			|| (name[*i + ft_strlen(env->content->key)] >= 9
				&& name[*i + ft_strlen(env->content->key)] == 13)
			|| name[*i + ft_strlen(env->content->key)] == '\"'
			|| name[*i + ft_strlen(env->content->key)] == '\''
			|| name[*i + ft_strlen(env->content->key)] == '$'))
		return (1);
	else
		return (0);
}

static char	*expand_exit_code(char *ret, int *i)
{
	char	*tmp;

	// #TODO: En el itoa hay que pasar la variable global que contiene el exit code del ultimo comando
	tmp = ft_itoa(127);
	ret = ft_strappend(ret, tmp);
	free(tmp);
	(*i)++;
	return (ret);
}

static char	*expand_env(char *ret, char *name, int *i, t_env *env)
{
	char	*tmp;
	int		expanded;

	tmp = NULL;
	expanded = 0;
	while (env)
	{
		if (check_exp_env(name, i, env))
		{
			tmp = ft_strdup(env->content->value);
			ret = ft_strappend(ret, tmp);
			free(tmp);
			*i += ft_strlen(env->content->key);
			expanded = 1;
			break ;
		}
		env = env->next;
	}
	if (!expanded)
	{
		tmp = ft_strdup("");
		ret = ft_strappend(ret, tmp);
		free(tmp);
		while (name[*i] && name[*i] != ' ')
			(*i)++;
	}
	return (ret);
}

char	*expand_lit(char *ret, char *name, int *i)
{
	char	lit[2];

	lit[0] = name[*i];
	lit[1] = '\0';
	ret = ft_strappend(ret, lit);
	(*i)++;
	return (ret);
}

char	*expand_dolar(char *name, t_env *env, int *quote, int *split)
{
	char	*ret;
	int		i;
	int		single_quote;

	i = 0;
	ret = ft_strdup("");
	single_quote = 0;
	while (name[i])
	{
		if (name[i] == '\"')
			(*quote) = 1;
		if (name[i] == '\'' && !(*quote))
		{
			if (single_quote)
				single_quote = 0;
			else
			{
				(*quote) = 1;
				single_quote = 1;}
		}
		if (name[i] == '$' && !single_quote)
		{
			i++;
			if (name[i] == '?')
				ret = expand_exit_code(ret, &i);
			else
			{
				ret = expand_env(ret, name, &i, env);
				if (!single_quote)
					(*split) = 1;
			}
		}
		else
			ret = expand_lit(ret, name, &i);
	}
	return (ret);
}
