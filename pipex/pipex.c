/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:04:16 by smeixoei          #+#    #+#             */
/*   Updated: 2024/08/06 19:04:16 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_waitchild(pid_t *child, int cmds)
{
	int		status;
	pid_t	wait;
	int		i;

	i = 0;
	while (i < cmds)
	{
		wait = waitpid(child[i], &status, 0);
		if (wait == -1)
			ft_error("Error: waitpid", NULL);
		i++;
	}
}

void	ft_pipex(int argc, char **argv, char **env)
{
	int		fd[2][2];
	pid_t	*child;
	int		i;

	i = 0;
	child = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!child)
		ft_error("Error: malloc", NULL);
	if (pipe(fd[0]) < 0)
		ft_error("Error: pipe", NULL);
	child[i++] = ft_first_cmd(fd, argv, env);
	child[i++] = ft_last_cmd(fd, argv, env, argc);
	ft_waitchild(child, i);
	free(child);
}

void	ft_pipex_bonus(int argc, char **argv, char **env)
{
	int		fd[2][2];
	int		cmds;
	int		here_doc;
	int		i;
	pid_t	*child;

	here_doc = 0;
	i = 0;
	child = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!child)
		ft_error("Error: malloc", NULL);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc = 1;
	if (pipe(fd[0]) < 0)
		ft_error("Error: pipe", NULL);
	cmds = 2 + here_doc;
	child[i++] = ft_first_cmd(fd, argv, env);
	while (++cmds < argc - 2)
		child[i++] = ft_mid_cmd(fd, argv, env, cmds);
	child[i++] = ft_last_cmd(fd, argv, env, argc);
	ft_waitchild(child, i);
	free(child);
}

// void	ft_leaks(void)
// {
// 	system("leaks -q pipex");
// }

int	main(int argc, char **argv, char **env)
{
	// atexit(ft_leaks);
	if (argc < 5 || ((ft_strncmp(argv[1], "here_doc", 9) == 0) && argc < 6))
		ft_error("Error: invalid arguments", NULL);
	if (BONUS == 0 && argc == 5)
		ft_pipex(argc, argv, env);
	else if (BONUS == 1 && argc >= 5)
		ft_pipex_bonus(argc, argv, env);
	else
		ft_error("Error: invalid arguments", NULL);
	return (0);
}
