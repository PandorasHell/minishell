/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:33:12 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:28:34 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_without_flag(char **cmd, int *i, int j)
{
	while ((*i) < j)
	{
		if (cmd[(*i) + 1] == NULL)
			printf("%s\n", cmd[(*i)]);
		else
			printf("%s ", cmd[(*i)]);
		(*i)++;
	}
}

static void	print_with_flag(char **cmd, int *i, int j)
{
	while ((*i) < j)
	{
		if (cmd[(*i) + 1] == NULL)
			printf("%s", cmd[(*i)]);
		else
			printf("%s ", cmd[(*i)]);
		(*i)++;
	}
}

static int	flag_checker(char **cmd, int iterator)
{
	int	j;

	while (cmd[iterator])
	{
		j = 1;
		if (cmd[iterator][0] == '-' && cmd[iterator][1])
		{
			while (cmd[iterator][j])
			{
				if (cmd[iterator][j] != 'n' && cmd[iterator][j] != '\0')
					return (iterator);
				j++;
			}
		}
		else
			return (iterator);
		iterator++;
	}
	return (iterator);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (cmd[j])
		j++;
	if (j == 1)
	{
		printf("\n");
		return (0);
	}
	i = flag_checker(cmd, i);
	if (i > 1)
		print_with_flag(cmd, &i, j);
	else
		print_without_flag(cmd, &i, j);
	return (0);
}
