/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:34:20 by smeixoei          #+#    #+#             */
/*   Updated: 2024/02/21 19:34:20 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	ft_waitchild(pid_t child)
{
	int		status;
	pid_t	wait;

	wait = waitpid(child, &status, 0);
	while (wait != child)
	{
		if (wait == -1)
			ft_error("Error: command not found");
	}
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			ft_error("Error: command not found");
	}
}

void	ft_pipex(int argc, char **argv, char **env)
{
	int		fd[2][2];
	pid_t	child;

	child = 0;
	if (pipe(fd[0]) < 0)
		ft_error("Error: pipe");
	ft_first_cmd(fd, argv, env);
	child = ft_last_cmd(fd, argv, env, argc);
	ft_waitchild(child);
}

void	ft_pipex_bonus(int argc, char **argv, char **env)
{
	int		fd[2][2];
	int		cmds;
	int		here_doc;
	pid_t	child;

	here_doc = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc = 1;
	if (pipe(fd[0]) < 0)
		ft_error("Error: pipe");
	cmds = 2 + here_doc;
	ft_first_cmd(fd, argv, env);
	while (++cmds < argc - 2)
		ft_mid_cmd(fd, argv, env, cmds);
	child = ft_last_cmd(fd, argv, env, argc);
	ft_waitchild(child);
}

// void	ft_leaks(void)
// {
// 	system("leaks -q pipex");
// }

int	main(int argc, char **argv, char **env)
{
	// atexit(ft_leaks);
	if (argc < 5 || ((ft_strncmp(argv[1], "here_doc", 9) == 0) && argc < 6))
		ft_error("Error: invalid arguments");
	if (BONUS == 0 && argc == 5)
		ft_pipex(argc, argv, env);
	else if (BONUS == 1 && argc >= 5)
		ft_pipex_bonus(argc, argv, env);
	else
		ft_error("Error: invalid arguments");
	return (0);
}
