/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/09/05 12:55:06 by smeixoei         ###   ########.fr       */
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

#define WORD 0
#define INFILE 1
#define HEREDOC 2
#define OUTFILE 3
#define APPEND 4
#define PIPE 5


// ENVIROMENT
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

// LEXER
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

// PARSER
typedef struct s_data_cmd
{
	char	*value;
	struct s_data_cmd *next;	
}	t_dcmd;

typedef struct s_data_redir_cmd
{
	char	*where;
	int		type;	
}	t_drcmd;

typedef struct s_redir_cmd
{
	t_drcmd *content;	
	struct s_redir_cmd *next;
}	t_rcmd;

typedef struct s_inter_cmd
{
	t_dcmd	*word;
	t_rcmd	*redir;
}	t_icmd;

typedef struct s_cmd
{
	t_icmd *content;
	struct s_cmd *next;
}	t_cmd;

// ENV
t_lenv	*save_env(char **env);

// LEXER
int	is_space(char c);
int	is_operator(char c);
int is_quote(char c);
t_lword	*split_words(char *line, t_lword *words);
t_lexer *lexical_analysis(char *line);

//PARSER
t_cmd	*final_cmd(t_lexer *lexer);

#endif