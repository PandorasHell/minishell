#include "../../minishell.h"

t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	// Parameter expansion
	// Word splitting
	// Quote Remove

	// La expansión de parametros sólo se etendrá en cuenta $ seguido de caracteres (Sólo el funcionamiento sin llaves). No opciones especiales como:
			// ${parameter:-word}
			// ${parameter@operator}

	// Hay que crear una nueva estructura t_cmd con los nuevos valores que asignan las expansiones.
	// 
	
	// Hay que comprobar y expandir (Si fuera necesario) todos los nodos de la lista cmd->info->word->name
	// También comprobar y expandir (Si fuera necesario) todos los fd apuntados por redirecciones cmd->info->redir->content->where

	// Las variables que estén dentro de comillas dobles sí se expanden
	// $? expande al último estado de salida ejecutado 

	// Eliminar las comillas, si tuvieran, que no sean resultado de las expansiones
}
