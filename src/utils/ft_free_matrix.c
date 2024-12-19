/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:34:38 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:34:39 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	matrix_counter(char **matrix)
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
