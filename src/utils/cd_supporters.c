#include "../../minishell.h"

/*
static t_env	*recreate_old_pwd(char *command, char *)
{
	t_env	*old_pwd;
	t_denv	*data;

	old_pwd = (t_env *)malloc(sizeof(t_env));
	data = (t_denv *)malloc(sizeof(t_denv));
	if (!data)
		return (NULL);
	data->key = ft_substr(command, 0, \
		ft_strchr(command, '=') - command);
	if (!data->key)
	{
		free(data);
		return (NULL);
	}
	data->value = ft_strdup(ft_strchr(command, '=') + 1);
	if (!data->value)
	{
		free(data->key);
		free(data);
		return (NULL);
	}
	old_pwd->content = data;
	return (old_pwd);
}

 int	pwd_changer(t_env *env, char *path)
 {
 	char *tmp;
 	t_env *pwd;
 	t_env *oldpwd;

 	pwd = pwd_finder("PWD", env);
 	if (!pwd)
 		return (1);
 	tmp = pwd->content->value;
 	pwd->content->value =
 	oldpwd = pwd_finder("OLDPWD", env);
 	if (!oldpwd)
 		return (0);
 	tmp = oldpwd->content->value;
 	oldpwd->content->value = pwd->content->value;
 }
*/
//TODO: HACER ESTA FUNCION
t_env *pwd_finder_unset(char *key, int *j, t_env *env)
{
	t_env *tmp;

	tmp = env;
	if (ft_strcmp(tmp->content->key, key) == 0)
		return (tmp);
	while(tmp)
	{
		(*j)++;
		if (ft_strcmp(tmp->next->content->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env *pwd_finder(char *key, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while(tmp)
	{
		if (ft_strcmp(tmp->content->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
