#include "../../minishell.h"

static char	*ft_read(int fd, char *rf)
{
	char	*nl;
	int		bytes;

	bytes = 1;
	nl = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!nl)
		return (NULL);
	while (!ft_strchr(rf, '\n') && bytes != 0)
	{
		bytes = read(fd, nl, BUFFER_SIZE);
        if (g_handler == SIGINT)
        {
			free(nl);
        	return (NULL);
        }
		if (bytes < 0)
		{
			free(nl);
			return (NULL);
		}
		nl[bytes] = '\0';
		rf = ft_strappend(rf, nl);
	}
	free(nl);
	return (rf);
}

char	*ft_line(char *rf)
{
	char	*line;
	int		i;

	i = 0;
	if (!rf || rf[0] == '\0')
		return (NULL);
	while (rf[i] != '\0' && rf[i] != '\n')
		i++;
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (rf[i] != '\n' && rf[i] != '\0')
	{
		line[i] = rf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_rst(char *rf)
{
	char	*rst;
	int		i;
	int		j;

	i = 0;
	while (rf[i] != '\n' && rf[i] != '\0')
		i++;
	if (rf[i] == '\0')
	{
		free(rf);
		return (NULL);
	}
	rst = ft_calloc((ft_strlen(rf) - i + 1), sizeof(char));
	if (!rst)
		return (NULL);
	i++;
	j = 0;
	while (rf[i] != '\0')
		rst[j++] = rf[i++];
	rst[j] = '\0';
	free(rf);
	return (rst);
}

char	*get_next_line(int fd)
{
	static char	*rf;
	char		*line;

	if (read(fd, 0, 0) < 0 || fd < 0)
	{
		free(rf);
		rf = NULL;
		return (NULL);
	}
	if (!rf)
	{
		rf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!rf)
			return (NULL);
	}
	rf = ft_read(fd, rf);
	if (g_handler == SIGINT)
	{
		free(rf);
		return (NULL);
	}
	if (!rf)
		return (NULL);
	line = ft_line(rf);
	rf = ft_rst(rf);

	return (line);
}
