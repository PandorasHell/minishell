
#include "../../minishell.h"

// static int double_ampersan_pipe_check(const char *line)
// {
// 	int index;

// 	index = -1;
// 	while(line[++index])
// 	{
// 		if (line[index] == '|')
// 		{
// 			if (line[index + 1] == '|')
// 				return (1);
// 		}
// 		else if (line[index] == '&')
// 		{
// 			if (line[index + 1] == '&')
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

static void space_remover(char *line)
{
	int i;
	int j;
	int spaceflag;

	i = 0;
	j = 0;
	spaceflag = 0;
	while(line[i])
	{
		if(line[i] != ' ')
		{
			line[j++] = line[i];
			spaceflag = 0;
		}
		else if (spaceflag == 0)
		{
			//TODO: crear una funcion que revise si, luego de conseguir un | hay otro o un & hay otro.
			line[j++] = line[i];
			spaceflag = 1;
		}
		i++;
	}
	line[j] = '\0';
}

t_lword *lexical_analysis(char *line)
{
	t_lword *words;

	space_remover(line);
	words = split_words(line);
	return (words);
}