#include "../../minishell.h"

void ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return ;
	printf("%s\n", pwd);
	free(pwd);
}
