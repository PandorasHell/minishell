/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/08/28 19:03:56 by smeixoei         ###   ########.fr       */
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

typedef struct s_line_word
{
	char *word;
	struct s_line_word *next;
}	t_lword;

typedef struct s_data_lexer
{
	int		key;
	char	*value;
}	t_dlexer;

typedef struct s_lexer
{
	t_dlexer *content;
	struct s_lexer *next;
}	t_lexer;

typedef struct s_aritmetics
{
	int value;
	struct s_aritmetics *next;
}	t_aritmetics;


void malloc_check(void *str);
t_aritmetics *a_node_creator(t_aritmetics *information, int value);
//int shell_aritmetics(char *str);

// ENV
t_lenv	*save_env(char **env);

// LEXER
int	is_space(char c);
int	is_operator(char c);
int is_quote(char c);
t_lword	*split_words(char *line, t_lword *words);
t_lexer *lexical_analysis(char *line);
#endif
