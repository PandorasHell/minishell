/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:11 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:19:11 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_mid(t_cmd *cmd, t_env *env, t_cmd_name *export_env)
{
	manage_redir(cmd->info->redir);
	if (ft_is_builtin(cmd->info->word->name))
	{
		exec_builtin(cmd, env, export_env);
		exit (0);
	}
	child_process(cmd, env);
}

pid_t	ft_first_cmd(int (*fd)[2], t_cmd *cmd, t_env *env, t_cmd_name *export_env)
{
	pid_t	pid_in;

	pid_in = fork();
	if (pid_in < 0)
	{
		perror("Error: fork failed");
		return (0);
	}
	if (pid_in == 0)
	{
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][0]);
		manage_redir(cmd->info->redir);
		if (ft_is_builtin(cmd->info->word->name))
		{
			exec_builtin(cmd, env, export_env);
			exit (0);
		}
		child_process(cmd, env);
	}
	close(fd[0][1]);
	return (pid_in);
}

pid_t	ft_mid_cmd(int (*fd)[2], t_cmd *cmd, t_env *env,
					t_cmd_name *export_env)
{
	pid_t	pid_mid;
	int		fd_mid[2];

	if (pipe(fd_mid) < 0)
	{
		perror("Error: pipe failed");
		return (0);
	}
	pid_mid = fork();
	if (pid_mid < 0)
		return (1);
	if (pid_mid == 0)
	{
		close(fd[1][0]);
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd_mid[0]);
		dup2(fd_mid[1], STDOUT_FILENO);
		close(fd_mid[1]);
		exec_mid(cmd, env, export_env);
	}
	close(fd[0][0]);
	close(fd_mid[1]);
	fd[0][0] = fd_mid[0];
	return (pid_mid);
}

pid_t	ft_last_cmd(int (*fd)[2], t_cmd *cmd, t_env *env,
					t_cmd_name *export_env)
{
	pid_t	pid_out;

	pid_out = fork();
	if (pid_out < 0)
	{
		perror("Error: fork failed");
		return (0);
	}
	if (pid_out == 0)
	{
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd[1][1]);
		manage_redir(cmd->info->redir);
		if (ft_is_builtin(cmd->info->word->name))
		{
			exec_builtin(cmd, env, export_env);
			exit (0);
		}
		else
			child_process(cmd, env);
	}
	close(fd[0][0]);
	close(fd[1][1]);
	return (pid_out);
}
