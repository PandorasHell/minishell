#include "../../minishell.h"

char	*expand_dolar_heredoc(char *name, t_env *env)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (name[i])
	{
		if (name[i] == '$' && is_sys_var(name, &i))
		{
			i++;
			if (name[i] == '?')
				ret = expand_exit_code(ret, &i);
			else
				ret = expand_env(ret, name, &i, env);
		}
		else
			ret = expand_lit(ret, name, &i);
		if ((size_t)i >= ft_strlen(name))
			break ;
	}
	return (ret);
}
