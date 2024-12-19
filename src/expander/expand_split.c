/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:18:53 by smeixoei          #+#    #+#             */
/*   Updated: 2024/12/19 17:18:54 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//TODO: verificar que liberan las dos funciones auxiliares

static void	*free_word_split(char **split_words, t_cmd_name *new)
{
	cleanup(split_words);
	ft_lstclear((t_list **)&new, free);
	return (NULL);
}

static void	*free_redir_split(char **split_words, t_cmd_red *new)
{
	cleanup(split_words);
	if (new->content)
		free(new->content);
	if (new)
		free(new);
	return (NULL);
}

t_cmd_red	*expand_split_redir(char *name)
{
	t_cmd_red	*exp;
	t_cmd_red	*new;
	char		**split_words;
	int			i;

	split_words = ft_split(name, ' ');
	if (!split_words)
		return (NULL);
	exp = NULL;
	i = -1;
	while (split_words[++i])
	{
		new = ft_calloc(1, sizeof(t_cmd_red));
		if (!new)
			return (free_redir_split(split_words, new));
		new->content = ft_calloc(1, sizeof(t_cmd_dred));
		if (!new->content)
			return (free_redir_split(split_words, new));
		new->content->where = ft_strdup(split_words[i]);
		if (!new->content->where)
			return (free_redir_split(split_words, new));
		ft_lstadd_back((t_list **)&exp, (t_list *)new);
	}
	cleanup(split_words);
	return (exp);
}

t_cmd_name	*expand_split_word(char *name)
{
	t_cmd_name	*exp;
	t_cmd_name	*new;
	char		**split_words;
	int			i;

	split_words = ft_split(name, ' ');
	if (!split_words)
		return (NULL);
	exp = NULL;
	i = 0;
	while (split_words[i])
	{
		new = ft_calloc(1, sizeof(t_cmd_name));
		if (!new)
			return (free_word_split(split_words, new));
		new->name = ft_strdup(split_words[i]);
		if (!new->name)
			return (free_word_split(split_words, new));
		ft_lstadd_back((t_list **)&exp, (t_list *)new);
		i++;
	}
	cleanup(split_words);
	return (exp);
}
