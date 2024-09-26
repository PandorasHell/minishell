#include "../../minishell.h"

t_cmd_name	*expand_redir(t_cmd_name *name, t_env *env)
{
	// Ahora si hay que recorrer lo que contenga la lista t_cmd_name de cada comando y sustituir las expansiones.
	// Hay que comprobar cada nodo por si alguna de las opciones fuera un expansor.
	// No es necesario comprobar si contiene $ dentro de comillas simples, pero si de dobles.
	// En el caso de que sea $? hay qie hacer un itoa para imprimir el valor.
}