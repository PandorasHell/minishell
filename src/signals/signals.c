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
}

void child_signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		printf("\n");
		global_handler = -1;
	}
	else if (signal_number == SIGQUIT)
	{
		rl_replace_line(rl_line_buffer, 0);
		rl_redisplay();
		global_handler = -2;
	}

}

void ignored_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void child_signals(void)
{
	signal(SIGINT, &child_signal_handler);
	signal(SIGQUIT, &child_signal_handler);
}

void main_signals(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}