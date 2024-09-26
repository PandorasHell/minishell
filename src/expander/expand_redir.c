#include "../../minishell.h"

t_cmd_red	*expand_redir(t_cmd_red *redir, t_env *env)
{
	// Ahora si hay que recorrer cada nodo la lista t_cmd_red de cada comando y sustituir las expansiones.
	// En este caso ha que comprobar el valor where por si fuera una expansión.
}