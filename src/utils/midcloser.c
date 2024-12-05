#include "../../minishell.h"

int	midcloser_2(int (*fd)[2])
{
	if (close(fd[1][0]) < 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	if (close(fd[0][0]) < 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	return (0);
}

int	midcloser_1(int fd_mid[2])
{
	if (close(fd_mid[1]) < 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	if (close(fd_mid[1]) < 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	return (0);
}
