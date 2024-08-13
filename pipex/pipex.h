/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:58:55 by smeixoei          #+#    #+#             */
/*   Updated: 2024/08/06 19:00:53 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BONUS 1

void	ft_pipex(int argc, char **argv, char **env);
void	ft_pipex_bonus(int argc, char **argv, char **env);
void	ft_free_split(char **split);
void	ft_error(char *str, int *fd);
int		ft_heredoc(char *argv1, char *argv2);
pid_t	ft_first_cmd(int (*fd)[2], char **argv, char **env);
pid_t	ft_mid_cmd(int (*fd)[2], char **argv, char **env, int cmds);
pid_t	ft_last_cmd(int (*fd)[2], char **argv, char **env, int argc);
void	ft_waitchild(pid_t *child, int cmds);
char	*ft_get_path(char *cmd, char **env);
int		ft_relative_path(char **cmd, char **path);
void	ft_execute(char *argv, char **env);

#endif