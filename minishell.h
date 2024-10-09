/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/10/09 18:31:07 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft/libft.h"
# include "./pipex/pipex.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WORD 0
# define INFILE 1
# define HEREDOC 2
# define OUTFILE 3
# define APPEND 4
# define PIPE 5
# define REDIR 6

// ENVIROMENT
typedef struct s_data_env
{
	char				*key;
	char				*value;
}						t_denv;

typedef struct s_list_env
{
	t_denv				*content;
	struct s_list_env	*next;
}						t_env;

// LEXER
typedef struct s_line_word
{
	char				*word;
	struct s_line_word	*next;
}						t_lword;

typedef struct s_data_lexer
{
	int					key;
	char				*value;
}						t_dlexer;

typedef struct s_lexer
{
	t_dlexer			*content;
	struct s_lexer		*next;
}						t_lexer;

// PARSER
typedef struct s_cmd_name
{
	char				*name;
	struct s_cmd_name	*next;
}						t_cmd_name;

typedef struct s_cmd_data_redir
{
	char				*where;
	int					type;
}						t_cmd_dred;

typedef struct s_cmd_redir
{
	t_cmd_dred			*content;
	struct s_cmd_redir	*next;
}						t_cmd_red;

typedef struct s_cmd_data
{
	t_cmd_name			*word;
	t_cmd_red			*redir;
}						t_cmd_data;

typedef struct s_cmd
{
	t_cmd_data			*info;
	struct s_cmd		*next;
}						t_cmd;

// ENV
t_env					*save_env(char **env);
void					free_env(t_env *env);

// LEXER
int						is_space(char c);
int						is_operator(char c);
int						is_quote(char c);
t_lword					*split_words(char *line, t_lword *words);
t_lexer					*lexical_analysis(char *line);
void					free_lexer(t_lexer **lexer);
void					free_words(t_lword *words);

// PARSER
t_cmd					*complete_parser(t_lexer *lexer);
void					free_cmd(t_cmd *cmd);
t_cmd					*set_cmd_mem(void);
int						set_cmd_value(t_lexer **lexer, t_cmd *cmd);
int						status_pipe(t_lexer **lexer, int status);
int						status_redir(t_lexer **lexer, int status, t_cmd *cmd);

// EXPANDER
t_cmd					*expand_cmd(t_cmd *cmd, t_env *env);
int						expand_redir(t_cmd *redir, t_env *env, t_cmd *cmd);
int						expand_name(t_cmd *word, t_env *env, t_cmd *cmd);
char					*expand_dolar(char *name, t_env *env);

// UTILS
int						exit_checker(const char *line, const char *comparer);
int						check_character_for_history(char c);

#endif