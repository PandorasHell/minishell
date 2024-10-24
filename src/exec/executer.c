#include "../../minishell.h"

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	// Antes de hacer nada con el comando hay que resolver los heredocs
	// Eso incluye a todos los posibles heredocs, no unicamente los del primer comando
	// En el caso de tener heredoc se debe cerear un nuevo documento por cada uno
	// (que se tiene que crear y destruir en la carpeta /tmp)
	// a la hora de ejecutar los comandos.
	// Hay ue volver a crear una nueva lista de redirecciones con esto "expandido"
	if (create_heredocs(cmd, env))
		return (NULL);
	if (ft_lstsize((t_list **)cmd) == 1)
	{
		if (is_built_in(cmd->info->word->name))
			execute_built_in(cmd);
		else
			execute_one(cmd, env);
	}
	else
		execute_cmd(cmd, env);

	// Luego de resolver los heredocs, pasamos a ir ejecutando los comandos
	// Antes de ponernos a mander execve, tenemos que resolver las redirecciones
	// Para eso podemos intentar utilizar todo lo del pipex
	// Aunque vamos a tener que convertir las listas de env y de cmd->word a arrays
	// Para poder pasarlos a execve

	// Y creo que ya, a saber como vamos a integrar todo, pero confio xd
}
