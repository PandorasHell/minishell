/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:37 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:28:30 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	double_quote_status(t_quote *quot, int *i, int *split, char *name)
{
	while (name[*i] == '\"')
	{
		if (quot->d_quote)
			quot->d_quote = 0;
		else
		{
			(*split) += 1;
			quot->d_quote = 1;
		}
		(*i)++;
	}
	if (name[*i] == '\'' && quot->d_quote == 0)
		single_quote_status(quot, i, split, name);
}

void	single_quote_status(t_quote *quot, int *i, int *split, char *name)
{
	while (name[*i] == '\'')
	{
		if (quot->s_quote)
			quot->s_quote = 0;
		else
		{
			(*split) += 1;
			quot->s_quote = 1;
		}
		(*i)++;
	}
	if (name[*i] == '\"' && quot->s_quote == 0)
		double_quote_status(quot, i, split, name);
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

char	*expand_dolar(char *name, t_env *env, int *split)
{
	char	*ret;
	int		i;
	t_quote	*quote;

	i = 0;
	ret = ft_strdup("");
	quote = ft_calloc(1, sizeof(t_quote));
	while (name[i])
	{
		if (name[i] == '\"' && !quote->s_quote)
			double_quote_status(quote, &i, split, name);
		else if (name[i] == '\'' && !quote->d_quote)
			single_quote_status(quote, &i, split, name);
		if (name[i] == '$' && !quote->s_quote)
			ret = expand_dolar_case(ret, name, &i, env);
		else
			ret = expand_lit(ret, name, &i);
		if ((size_t)i >= ft_strlen(name))
			break ;
	}
	free(quote);
	return (ret);
}
