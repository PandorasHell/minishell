/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_freer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:35:19 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 17:35:20 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_pointer_free(void *ptr, void *ptr2, void *ptr3, int flag)
{
	if (flag == 1)
		free(ptr);
	if (flag == 2)
	{
		free(ptr);
		free(ptr2);
	}
	if (flag == 3)
	{
		free(ptr);
		free(ptr2);
		free(ptr3);
	}
	return (1);
}

int	pointer_free(void *ptr, void *ptr2, void *ptr3, int flag)
{
	if (flag == 1)
		free(ptr);
	if (flag == 2)
	{
		free(ptr);
		free(ptr2);
	}
	if (flag == 3)
	{
		free(ptr);
		free(ptr2);
		free(ptr3);
	}
	return (0);
}
