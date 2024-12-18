#include "../../minishell.h"


void export_foo_creator(t_cmd_name *exported_env, char *cmd)
{
    t_cmd_name *node;

    node = ft_calloc(1, sizeof(t_cmd_name)); 
    if (!node)
        exit(1);
    node->name = ft_substr(cmd, 0, ft_strlen(cmd));
    if (!node->name)
        exit(1);
    ft_lstadd_back((t_list **)&exported_env, (t_list *)node);
}

void export_env(t_cmd_name *exported_env, t_env *env)
{
    t_env       *tmp;
    t_cmd_name  *tmp2;

	tmp = env;
	if (!tmp)
        exit(1);
	while (tmp)
	{
		if (tmp->content->value)
			printf("declare -x %s=%s\n", tmp->content->key, tmp->content->value);
		tmp = tmp->next;
	}
    tmp2 = exported_env;
    while (tmp2)
    {
        if (tmp2->name)
            printf("declare -x %s\n", tmp2->name);
        tmp2 = tmp2->next;
    }
}