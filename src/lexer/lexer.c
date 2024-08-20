
#include "../../minishell.h"

t_lword *lexical_analysis(char *line)
{
	t_lword *words;

	words = split_words(line);
	return (words);
}