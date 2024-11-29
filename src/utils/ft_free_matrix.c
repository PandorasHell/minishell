#include "../../minishell.h"

int		matrix_counter(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	free_matrix(char ***matrix)
{
	int	i;
	int	j;

	j = 0;
	while (matrix[j])
	{
		i = -1;
		while (matrix[j][++i])
			free(matrix[j][i]);
		free(matrix[j]);
		j++;
	}
	free(matrix);
}
