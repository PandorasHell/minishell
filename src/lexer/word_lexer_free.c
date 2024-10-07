#include "../../minishell.h"

void	free_words(t_lword *words)
{
	t_lword	*temp;

	temp = words;
	while (words)
	{
		words = words->next;
		free(temp->word);
		free(temp);
		temp = words;
	}
}
