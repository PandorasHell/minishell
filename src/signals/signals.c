#include "../../minishell.h"

void signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		global_handler = -1;
	}
	else if (signal_number == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		global_handler = SIGQUIT;
	}
}

void child_signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		printf("\n");
		global_handler = SIGINT;
	}
	else if (signal_number == SIGQUIT)
	{
		global_handler = SIGQUIT;
	}

}

void ignored_signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}

void child_signals(void)
{
	if (signal(SIGINT, child_signal_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, child_signal_handler) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}

void main_signals(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		perror("Error setting SIGINT handler");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("Error setting SIGQUIT handler");
}