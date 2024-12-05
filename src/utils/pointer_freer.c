#include "../../minishell.h"

int	error_pointer_free(void *ptr, void *ptr2, void *ptr3, int flag)
{
	if (flag == 1)
		free(ptr);
	if (flag == 2)
	{
		free(ptr);
		free(ptr2);
	}
	if (flag == 3)
	{
		free(ptr);
		free(ptr2);
		free(ptr3);
	}
	return (1);
}

int	pointer_free(void *ptr, void *ptr2, void *ptr3, int flag)
{
	if (flag == 1)
		free(ptr);
	if (flag == 2)
	{
		free(ptr);
		free(ptr2);
	}
	if (flag == 3)
	{
		free(ptr);
		free(ptr2);
		free(ptr3);
	}
	return (0);
}
