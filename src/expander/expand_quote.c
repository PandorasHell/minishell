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

	if (!line)
		return (NULL);
	exp = NULL;
	i = ft_strlen(line) - 1;
	if (line[0] == '\"' || line[0] == '\''
		|| line[i] == '\"' || line[i] == '\'')
	{
		len = quote_len(line);
		if (!len)
			return (NULL);
		exp = ft_substr(line, 1, len - 1);
	}
	else
		exp = ft_strdup(line);
	free(line);
	return (exp);
}

