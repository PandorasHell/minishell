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
		rl_replace_line(rl_line_buffer, 0);
		rl_redisplay();
		global_handler = -2;
	}
}

void signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void signal_int(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void signal_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void signal_main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}