#include "../../minishell.h"


char	*append_path(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	s3 = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 2 * sizeof(char)));
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
    s3[i] = '/';
	i++;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}
