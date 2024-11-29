#include "../../minishell.h"

static void free_single_node(t_env *node)
{
  t_env	*tmp;
  t_env *tmp2;
  t_env *tmp3;

  tmp = node;
  tmp = tmp;
  tmp2 = tmp->next;
  tmp3 = tmp->next->next;
  tmp->next = tmp3;
  free(tmp2->content->key);
  free(tmp2->content->value);
  free(tmp2->content);
  free(tmp2);
}

static void free_first_node(t_env *node)
{
  t_env *tmp;

  tmp = node;
  node = node->next;
  free(tmp->content->key);
  free(tmp->content->value);
  free(tmp->content);
  free(tmp);
}

int ft_unset(char **cmd, t_env *env)
{
  t_env *tmp;
  int   i;
  int   j;

  tmp = NULL;
  i = 0;
  j = 0;
  while (cmd[++i])
  {
    tmp = pwd_finder_unset(cmd[i], &j, env);
    if (j == 0)
      free_first_node(tmp);
    else if (j > 0)
      free_single_node(tmp);
  }
  tmp = env;
  return (0);
}
