/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:59 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:19:00 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*expand_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*exp;
	t_cmd	*new;
	t_cmd	*tmp;

	exp = NULL;
	tmp = cmd;
	while (tmp)
	{
		new = set_cmd_mem();
		if (!new)
		{
			ft_lstclear((t_list **)&exp, free);
			return (NULL);
		}
		if (expand_name(new, env, tmp) || expand_redir(new, env, tmp))
			return (ft_lstclear((t_list **)&exp, free), NULL);
		ft_lstadd_back((t_list **)&exp, (t_list *)new);
		tmp = tmp->next;
	}
	return (exp);
}
