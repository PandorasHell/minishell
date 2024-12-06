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

char	*expand_env(char *ret, char *name, int *i, t_env *env)
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
