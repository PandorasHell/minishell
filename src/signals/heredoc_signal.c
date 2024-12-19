/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:33:42 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 19:21:47 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	heredoc_signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		g_handler = SIGINT + 128;
	}
}

void	heredoc_signals(void)
{
	if (signal(SIGINT, heredoc_signal_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}
