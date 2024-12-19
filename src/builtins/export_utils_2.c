/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:33:20 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:33:21 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_exp_mid_node(t_cmd_name *node)
{
	t_cmd_name	*tmp;
	t_cmd_name	*tmp2;
	t_cmd_name	*tmp3;

	if (!node)
		return ;
	tmp = node;
	tmp2 = tmp->next;
	tmp3 = tmp->next->next;
	tmp->next = tmp3;
	free(tmp2->name);
	free(tmp2);
}

void	free_exp_first_node(t_cmd_name *node)
{
	t_cmd_name	*tmp;

	if (!node)
		return ;
	tmp = node;
	node = node->next;
	free(tmp->name);
	free(tmp);
}
