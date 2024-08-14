

#include "../../minishell.h"


t_aritmetics *a_node_creator(t_aritmetics *information, int value)
{
	t_aritmetics *node;
	t_aritmetics *temp_node;

	if (!information)
	{
		node = malloc(sizeof(t_aritmetics));
		malloc_check(node);
		node->next = NULL;
		node->value = value;
	}
	else
	{
		temp_node = information;
		while (temp_node->next != NULL)
			information = information->next;
		node = malloc(sizeof(t_aritmetics));
		malloc_check(temp_node);
		node->value = value;
		node->next = node;
	}
	return (information);
}