


#include "../../minishell.h"



void malloc_check(void *str)
{
	if (!str)
	{
		perror("A malloc has failed");
		exit(1);
	}
}