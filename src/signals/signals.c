/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:33:44 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:33:45 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_handler = SIGINT;
	}
	else if (signal_number == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_handler = SIGQUIT;
	}
}

void	child_signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		g_handler = SIGINT;
	}
	else if (signal_number == SIGQUIT)
	{
		g_handler = SIGQUIT;
	}
}

void	ignored_signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}

void	child_signals(void)
{
	if (signal(SIGINT, child_signal_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, child_signal_handler) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}

void	main_signals(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}
