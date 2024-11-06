#include "../../minishell.h"

void ft_pwd(void)
{
  char *current_path;

  current_path = getcwd(NULL, 0);
  if (!current_path)
  {
    ft_putstr_fd("Path error", 2);
    return ;
  }
  else
    printf("%s\n", current_path);
}

//TODO: mejorar el codigo de error en caso de que no consiga el path