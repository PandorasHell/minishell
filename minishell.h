/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/09/13 20:47:34 by smeixoei         ###   ########.fr       */
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
#define REDIR 6

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
typedef struct s_cmd_name
{
	char	*name;
	struct s_cmd_name *next;	
}	t_cmd_name;

typedef struct s_cmd_data_redir
{
	char	*where;
	int		type;
}	t_cmd_dred;

typedef struct s_cmd_redir
{
	t_cmd_dred *content;	
	struct s_cmd_redir *next;
}	t_cmd_red;

typedef struct s_cmd_data
{
	t_cmd_name	*word;
	t_cmd_red	*redir;
}	t_cmd_data;

typedef struct s_cmd
{
	t_cmd_data *info;
	struct s_cmd *next;
}	t_cmd;

// ENV
t_lenv	*save_env(char **env);
void	free_env(t_lenv *env);

// LEXER
int	is_space(char c);
int	is_operator(char c);
int is_quote(char c);
t_lword	*split_words(char *line, t_lword *words);
t_lexer *lexical_analysis(char *line);
void	free_lexer(t_lexer **lexer);
void free_words(t_lword *words);

//PARSER
t_cmd	*final_cmd(t_lexer *lexer);
void	free_cmd(t_cmd *cmd);
t_cmd	*set_cmd_mem(t_cmd *cmd);
// t_dcmd	*set_cmd_word(t_lexer *lexer);
// t_rcmd	*set_cmd_redir(t_lexer *lexer);
int	set_cmd_value(t_lexer **lexer, t_cmd *cmd);
int status_pipe(t_lexer **lexer, int status);
int status_redir(t_lexer **lexer, int status, t_cmd *cmd);

//UTILS
int exit_checker(const char *line, const char *comparer_exit);

#endif