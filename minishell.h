/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:52:54 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/12 18:48:08 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <bits/signum-generic.h>
# include <sys/ioctl.h>

# define WORD 0
# define INFILE 1
# define HEREDOC 2
# define OUTFILE 3
# define APPEND 4
# define PIPE 5
# define REDIR 6

extern int g_handler;

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
t_env		*save_env(char **env);
void		free_env(t_env **env);

// LEXER
int			is_space(char c);
int			is_operator(char c);
int			is_quote(char c);
t_cmd_name	*split_words(char *line, t_cmd_name *words);
t_lexer		*lexical_analysis(char *line);
void		free_lexer(t_lexer **lexer);

// PARSER
t_cmd		*complete_parser(t_lexer *lexer);
void		free_cmd(t_cmd *cmd);
t_cmd		*set_cmd_mem(void);
int			set_cmd_value(t_lexer **lexer, t_cmd *cmd);
int			status_pipe(t_lexer **lexer, int status);
int			status_redir(t_lexer **lexer, int status, t_cmd *cmd);

// EXPANDER
t_cmd		*expand_cmd(t_cmd *cmd, t_env *env);
int			expand_redir(t_cmd *redir, t_env *env, t_cmd *cmd);
int			expand_name(t_cmd *word, t_env *env, t_cmd *cmd);
char		*expand_dolar(char *name, t_env *env, int *quote);
char		*expand_lit(char *ret, char *name, int *i);
char		*expand_env(char *ret, char *name, int *i, t_env *env);
char		*expand_exit_code(char *ret, int *i);
t_cmd_name	*expand_split_word(char *name);
t_cmd_red	*expand_split_redir(char *name);
char		*expand_dolar_heredoc(char *name, t_env *env);
void		double_quote_status(int *double_quote, int *i, int *quote,
								char *name, int *single_quote);
void		single_quote_status(int *single_quote, int *i, int *quote, char *name, int *double_quote);

// EXECUTER
void		exec_cmd(t_cmd *cmd, t_env *env, t_cmd_name *export_env);
int			create_heredoc(t_cmd *cmd, t_env *env);
void		free_redir(t_cmd_red *redir);
char		*remove_quotes(char *limiter);
char		*new_file(int *status);
char		*create_tmp_file(char *limiter, int *status, int *fd, char **name);
void		execute_one(t_cmd *cmd, t_env *env, t_cmd_name *export_env);
int			relative_path(char **cmd, char **path);
char		*get_path(char *cmd, char **env);
char		**env_to_array(t_env *env);
char		**cmd_to_array(t_cmd_name *cmd);
int			manage_redir(t_cmd_red *redir);
void		manage_only_redir_line(t_cmd_red *redir);
void		execute_n(t_cmd *cmd, t_env *env, t_cmd_name *exported_env);
void		child_process(t_cmd *cmd, t_env *env);
pid_t		ft_first_cmd(int (*fd)[2], t_cmd *cmd, t_env *env,
						 t_cmd_name *export_env);
pid_t		ft_mid_cmd(int (*fd)[2], t_cmd *cmd, t_env *env, 
						t_cmd_name *export_env);
pid_t		ft_last_cmd(int (*fd)[2], t_cmd *cmd, t_env *env, 
						t_cmd_name *export_env);

// UTILS
int			exit_checker(const char *line, const char *comparer);
int			check_character_for_history(char c);
int			ft_strcmp(const char *s1, const char *s2);
t_env		*env_node_search(char *key, t_env *env);
t_env		*unset_node_search(char *key, int *j, t_env *env);
void		free_matrix(char ***matrix);
int			matrix_counter(char **matrix);
int			pointer_free(void *ptr, void *ptr2, void *ptr3, int flag);
int			error_pointer_free(void *ptr, void *ptr2, void *ptr3, int flag);
char		*append_path(char const *s1, char const *s2);
int			is_sys_var(char *name, int *pos);
long		ft_atol(const char *str);

// BUILTINS
int			ft_cd(char **cmd, t_env *env);
int			ft_echo(char **cmd);
int			ft_env(t_env *env);
int			ft_export(char **cmd, t_env *env, t_cmd_name *export_env);
int			ft_pwd(void);
int			ft_unset(char **cmd, t_env *env);
int			ft_is_builtin(char *cmd);
int			ft_exit(char **cmd_matrix, t_cmd *cmd, t_env *env);
int			exec_builtin(t_cmd *cmd, t_env *env, t_cmd_name *export_env);
void		exp_node_control(t_cmd_name *node, t_cmd_name *export_env, int counter);
int			variable_updater(char **cmd_matrix, t_env **env);
int			cmd_checker(char *cmd);
int			path_update_control(char *old_path, t_env *env);
void		export_env(t_cmd_name *exported_env, t_env *env);
void		export_foo_creator(char *cmd, t_cmd_name *exported_env, t_env *env);
int			save_node_env(char **cmd_matrix, t_env *env);
void		free_exp_first_node(t_cmd_name *node);
void		free_exp_mid_node(t_cmd_name *node);
t_cmd_name	*exp_node_search(char *cmd, int *node_counter, t_cmd_name *export_env);


// SIGNALS
void		ignored_signals(void);
void		main_signals(void);
void		child_signals(void);
void		heredoc_signals(void);

// GET_NEXT_LINE
char		*get_next_line(int fd);




#endif