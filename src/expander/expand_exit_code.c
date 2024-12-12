#include "../../minishell.h"

char	*expand_exit_code(char *ret, int *i)
{
	char	*tmp;

	// #TODO: En el itoa hay que pasar la variable global que contiene el exit code del ultimo comando
	tmp = ft_itoa(g_handler);
	ret = ft_strappend(ret, tmp);
	free(tmp);
	(*i)++;
	return (ret);
}
