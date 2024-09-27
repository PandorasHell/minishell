#include "../../minishell.h"

t_cmd_name	*expand_redir(t_cmd_name *name, t_env *env, t_cmd *cmd)
{

	t_cmd_name	*new;

	new = ft_calloc(1, sizeof(t_cmd_name));
	if (!new)
		return (ft_lstclear((t_list **)&new, free), NULL);
	new->name = expand_value();
	if (!new->name)
		return (ft_lstclear((t_list **)&new, free), free(new), NULL);
	return (new);
	// Ahora si hay que recorrer lo que contenga la lista t_cmd_name de cada comando y sustituir las expansiones.
	// Hay que comprobar cada nodo por si alguna de las opciones fuera un expansor.
	// No es necesario comprobar si contiene $ dentro de comillas simples, pero si de dobles.
	// En el caso de que sea $? hay qie hacer un itoa para imprimir el valor.
}