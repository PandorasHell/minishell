#include "../../minishell.h"

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	// Antes de hacer nada con el comando hay que resolver los heredocs
	// Eso incluye a todos los posibles heredocs, no unicamente los del primer comando

	// Luego de resolver los heredocs, pasamos a ir ejecutando los comandos
	// Antes de ponernos a mander execve, tenemos que resolver las redirecciones
	// Para eso podemos intentar utilizar todo lo del pipex
	// Aunque vamos a tener que convertir las listas de env y de cmd->word a arrays
	// Para poder pasarlos a execve

	// Y creo que ya, a saber como vamos a integrar todo, pero confio xd
}
