/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:50:16 by smeixoei          #+#    #+#             */
/*   Updated: 2024/02/21 20:50:16 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_heredoc(char *here_doc, char *limiter)
{
	char	*line;
	int		temp_fd;

	temp_fd = open(here_doc, O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 10)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	close(temp_fd);
	temp_fd = open(here_doc, O_RDONLY);
	return (temp_fd);
}

void	ft_first_cmd(int (*fd)[2], char **argv, char **env)
{
	pid_t	pid_in;
	int		fd_in;

	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		fd_in = ft_heredoc(argv[1], argv[2]);
	else
		fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		ft_error("Error: open");
	pid_in = fork();
	if (pid_in < 0)
		ft_error("Error: fork");
	if (pid_in == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][0]);
		ft_execute(argv[2], env);
	}
	close(fd_in);
	close(fd[0][1]);
}

void	ft_mid_cmd(int (*fd)[2], char **argv, char **env, int cmds)
{
	pid_t	pid_mid;
	int		fd_mid[2];

	if (pipe(fd_mid) < 0)
		ft_error("Error: pipe");
	pid_mid = fork();
	if (pid_mid < 0)
		ft_error("Error: fork");
	
	if (pid_mid == 0)
	{
		close(fd[1][0]);
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd_mid[0]);
		dup2(fd_mid[1], STDOUT_FILENO);
		close(fd[0][0]);
		close(fd_mid[1]);
		ft_execute(argv[cmds], env);
	}
	close(fd[0][0]);
	close(fd_mid[1]);
	fd[0][0] = fd_mid[0];
	fd[1][1] = fd_mid[1];
}

pid_t	ft_last_cmd(int (*fd)[2], char **argv, char **env, int argc)
{
	pid_t	pid_out;
	int		fd_out;

	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out < 0)
		ft_error("Error: open");
	pid_out = fork();
	if (pid_out < 0)
		ft_error("Error: fork");
	if (pid_out == 0)
	{
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		ft_execute(argv[argc - 2], env);
	}
	close(fd[0][0]);
	close(fd_out);
	return (pid_out);
}
