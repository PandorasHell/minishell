#include "../../minishell.h"

int is_sys_var(char *name)
{
    int i;

    i = 1;
    if (name[0] == '_' || ft_isalpha(name[0]) || name[0] == '?')
        i++;
    else
        return (0);
    while (name[i] && name[i] != ' ' && name[i] != '=' && name[i] != '/')
    {
        printf("name[i]: %c\n", name[i]);
        if (name[i] == '_' || ft_isalpha(name[i]) || ft_isdigit(name[i]))
            i++;
        else
            return (0);
    }
    return (1);
}
