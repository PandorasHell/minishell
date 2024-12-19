#include "../../minishell.h"

static void	double_quote_status(int *double_quote, int *i, int *quote, char *name)
{
	while (name[*i] == '\"')
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
}

static void	single_quote_status(int *single_quote, int *i, int *quote, char *name)
{
	while (name[*i] == '\'')
	{
		if (*single_quote)
			*single_quote = 0;
		else
		{
			(*quote) += 1;
			*single_quote = 1;
		}
		(*i)++;
	}
}

static char	*expand_dolar_case(char *ret, char *name, int *i, t_env *env)
{
	(*i)++;
	if (!name[(*i)])
	{
		ret = ft_strappend(ret, "$");
		return (ret);
	}
	if (name[(*i)] == '?')
		ret = expand_exit_code(ret, i);
	else if (is_sys_var(name, i))
		ret = expand_env(ret, name, i, env);
	else
	{
		(*i)++;
		ret = expand_lit(ret, name, i);
	}
	return (ret);
}

char	*expand_dolar(char *name, t_env *env, int *quote)
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
		if (name[i] == '\"' && !single_quote)
			double_quote_status(&double_quote, &i, quote, name);
		if (name[i] == '\'' && !double_quote)
			single_quote_status(&single_quote, &i, quote, name);
		if (name[i] == '$' && !single_quote)
			ret = expand_dolar_case(ret, name, &i, env);
		else
			ret = expand_lit(ret, name, &i);
		if ((size_t)i >= ft_strlen(name))
			break ;
	}
	return (ret);
}
