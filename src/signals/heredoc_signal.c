#include "../../minishell.h"

static void heredoc_signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		g_handler = SIGINT;
	}
}

void heredoc_signals(void)
{
	if (signal(SIGINT, heredoc_signal_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}