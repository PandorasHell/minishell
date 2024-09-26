#include "../../minishell.h"

t_cmd_data	*paramenter_expansion(t_cmd_data *cmd, t_env *env)
{
	// La expansión de parametros sólo se tendrá en cuenta cundo sea $ seguido de caracteres (Sólo el funcionamiento sin llaves). No opciones especiales como:
			// ${parameter:-word}
			// ${parameter@operator}

	// Comprobar y expandir (Si fuera necesario) todos los nodos de la lista cmd->info->word->name
	expand_name(cmd->word, env);
	// Comprobar y expandir (Si fuera necesario) todos los fd apuntados por redirecciones cmd->info->redir->content->where
	expand_redir(cmd->redir, env);
	
	// $? expande al último estado de salida ejecutado 

	// Las variables que estén dentro de comillas dobles sí se expanden, pero no dentro ded las simples
}

t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*exp;
	t_cmd	*tmp;

	// La idea es crear una estructura t_cmd auxiliar para reasignar todos los datos de la estructura cmd que hay en main
	// Ya que todas las expansiones pueden crear nuevos nodos o variar el tamaño de los strings introducidos en algún comando
	tmp = cmd;
	// Como hay que comprobar todos los comandos con sus opciones y redirecciones tenia pensado hacer una bucle controlador de esto.
	while (cmd)
	{
		// Parameter expansion
		parameter_expansion(tmp->info, env);
		// Word splitting
		word_split();
		// Quote Remove ()
		quote_remove();
		ft_lstadd_back((t_list **)&exp, (t_list *)tmp);
		cmd = cmd->next;
	}
	retrun (exp);
	// Lo que no estoy segura es si se puede sobreescribir la que ya tenemos en el main para no necesitar crear una nueva.
	// De todas maneras va a haber que refactorizar la función principal porque no nos dan las lineas :(
}
