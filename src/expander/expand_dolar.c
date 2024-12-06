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

	expanded = ((tmp = NULL), 0);
	while (env)
	{
		if (check_exp_env(name, i, env))
		{
			tmp = ft_strdup(env->content->value);
			ret = ft_strappend(ret, tmp);
			free(tmp);
			*i += ((expanded = 1), ft_strlen(env->content->key));
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

static void	double_quote_status(int *double_quote, int *i, int *quote)
{
	if (*double_quote)
		*double_quote = 0;
	else
	{
		(*quote) += 1;
		*double_quote = 1;
	}
	(*i)++;
}

static void	single_quote_status(int *single_quote, int *i, int *quote)
{
	if (*single_quote)
		*single_quote = 0;
	else
	{
		(*quote) += 1;
		*single_quote = 1;
	}
	(*i)++;
};
// TODO: Dividir esto en dos

char	*expand_dolar(char *name, t_env *env, int *quote, int *split)
{
	char	*ret;
	int		i;
	int		single_quote;
	int		double_quote;

	i = 0;
	ret = ft_strdup("");
	single_quote = 0;
	double_quote = 0;
	while (name[i])
	{
		if (name[i] == '\"')
			double_quote_status(&double_quote, &i, quote);
		if (name[i] == '\'' && !double_quote)
			single_quote_status(&single_quote, &i, quote);
		if (name[i] == '$' && !single_quote)
		{
			i++;
			if (name[i] == '?')
				ret = expand_exit_code(ret, &i);
			else
			{
				ret = expand_env(ret, name, &i, env);
				(*split) = 1;
			}
		}
		else
			ret = expand_lit(ret, name, &i);
		if ((size_t)i >= ft_strlen(name))
			break ;
	}
	return (ret);
}
