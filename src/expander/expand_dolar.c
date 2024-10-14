#include "../../minishell.h"

int	check_exp_env(char *name, int *i, t_env *env)
{
	if (ft_strncmp(env->content->key, &name[*i],
			ft_strlen(env->content->key)) == 0
		&& (name[*i + ft_strlen(env->content->key)] == '\0'
			|| name[*i + ft_strlen(env->content->key)] == ' '
			|| (name[*i + ft_strlen(env->content->key)] >= 9
			&& name[*i + ft_strlen(env->content->key)] == 13)
			|| name[*i + ft_strlen(env->content->key)] == '\"'))
		return (1);
	else
		return (0);
}

char	*expand_exit_code(char *ret, int *i)
{
	char	*tmp;

	// En el itoa hay que pasar la variable global que contiene el exit code del ultimo comando
	tmp = ft_itoa(127);
	ret = ft_strappend(ret, tmp);
	free(tmp);
	(*i)++;
	return (ret);
}

char	*expand_env(char *ret, char *name, int *i, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	while (env)
	{
		if (check_exp_env(name, i, env))
		{
			tmp = ft_strdup(env->content->value);
			ret = ft_strappend(ret, tmp);
			free(tmp);
			*i += ft_strlen(env->content->key);
			break ;
		}
		env = env->next;
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

char	*expand_dolar(char *name, t_env *env, int *quote)
{
	char	*ret;
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
			{
				ret = expand_env(ret, name, &i, env);
				*quote = 1;
			}
		}
		else
			ret = expand_lit(ret, name, &i);
	}
	return (ret);
}
