#include "../../minishell.h"

static void free_single_node(t_env *tmp)
{
  free(tmp->content->key);
  free(tmp->content->value);
  free(tmp->content);
  free(tmp);
}

static t_env *delete_first_node(t_env *env)
{
  t_env *tmp;

  tmp = env;
  env = env->next;
  free_single_node(tmp);
  return (env);
}
//TODO: funcion que libera un nodo

int ft_unset(t_env *env, t_cmd *cmd)
{
  t_env *tmp;
  t_env *tmp2;
  t_env *tmp3;
  int   i;

  i = 0;
  tmp = env;
  while (tmp)
  {
    if (ft_strcmp((env->content->key, cmd->info->word->name) == 0)
    {
      if (i == 0)
      {
        env = delete_first_node(env);
        return (0);
      }
      if (tmp->next != NULL)
        tmp3 = tmp->next;
    }
    tmp2 = tmp;
    tmp = tmp->next;
  }
}