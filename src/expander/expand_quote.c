#include "../../minishell.h"

static int	quote_len(char *line)
{
	int		len;
	char	quote;

	quote = line[0];
	len = 1;
	while (line[len] && line[len] != quote)
		len++;
	return (len);
}

static char	*resolve_quote(char *line)
{
	int		i;
	int		len;
	char	*exp;

	i = ft_strlen(line) - 1;
	if (line[0] == '\"' || line[0] == '\'')
	{
		len = quote_len(line);
		if (!len)
			return (NULL);
		exp = ft_substr(line, 1, len - 1);
	}
	else if (line[i] == '\"' || line[i] == '\'')
	{
		len = quote_len(line);
		if (!len)
			return (NULL);
		exp = ft_substr(line, 0, len - 1);
	}
	else
		exp = ft_strdup(line);
	return (exp);
}

char	*expand_quote(char *line)
{
	char	*exp;

	if (!line)
		return (NULL);
	exp = resolve_quote(line);
	free(line);
	return (exp);
}
