/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/08/16 20:29:48 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./lib/libft/libft.h"
#include "./pipex/pipex.h"

typedef struct s_data_env
{
	char *key;
	char *value;
}	t_denv;

typedef struct s_list_env
{
	t_denv *content;
	struct s_list_env *next;
}	t_lenv;

typedef struct s_aritmetics
{
	int value;
	struct s_aritmetics *next;
}	t_aritmetics;


void malloc_check(void *str);
t_aritmetics *a_node_creator(t_aritmetics *information, int value);
int shell_aritmetics(char *str);

// ENV
t_lenv	*save_env(char **env);

#endif
