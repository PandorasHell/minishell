#include "../../minishell.h"

static int	quote_len(char *line)
{
	int		len;
	char	quote;

	quote = line[0];
	len = 1;
	while (line[len] && line[len] != quote)
		len++;
	if (line[len] == quote)
		return (len);
	return (0);
}

char	*expand_quote(char *line)
{
	char	*exp;
	int		len;
	int		i;
	int		j;

	exp = NULL;
	len = quote_len(line);
	i = 1;
	j = 0;
	exp = ft_calloc(len, sizeof(char));
	if (!exp)
		return  (NULL);
	while (i < len)
	{
		exp[j++] = line[i];
		i++;
	}

	printf("len: %d\n", len);
	printf("exp: %s\n", exp);
	free(line);
	return (exp);
}

