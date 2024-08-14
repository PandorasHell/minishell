/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/08/13 12:53:02 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include "./lib/libft/libft.h"
#include "./pipex/pipex.h"

typedef struct s_aritmetics
{
	int value;
	struct s_aritmetics *next;
}	t_aritmetics;


void malloc_check(void *str);
t_aritmetics *a_node_creator(t_aritmetics *information, int value);
int shell_aritmetics(char *str);

#endif
