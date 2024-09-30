#include "../../minishell.h"

t_cmd_data	*paramenter_expansion(t_cmd_data *info, t_env *env, t_cmd *cmd)
{
	// La expansión de parametros sólo se tendrá en cuenta cundo sea $ seguido de caracteres (Sólo el funcionamiento sin llaves). No opciones especiales como:
			// ${parameter:-word}
			// ${parameter@operator}

	// Comprobar y expandir (Si fuera necesario) todos los nodos de la lista cmd->info->word->name
	expand_name(info->word, env, cmd);
	// Comprobar y expandir (Si fuera necesario) todos los fd apuntados por redirecciones cmd->info->redir->content->where
	expand_redir(info->redir, env, cmd);
	// En esencia la expansión es la misma, lo único que cambia es donde se guarda.

	// $? expande al último estado de salida ejecutado 

	// Las variables que estén dentro de comillas dobles sí se expanden, pero no dentro ded las simples

	// Word splitting
	word_split(info);
	// Quote Remove
	quote_remove(info);
}

t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*exp;
	t_cmd	*tmp;

	exp = NULL;
	while (cmd)
	{
		tmp = set_cmd_mem(cmd);
		if (!tmp)
			return (ft_lstclear((t_list **)&cmd, free), NULL);
		paramenter_expansion(tmp->info, env, cmd);
		ft_lstadd_back((t_list **)&exp, (t_list *)tmp);
		cmd = cmd->next;
	}
	retrun (exp);
}
