

#include "../../minishell.h"








static int second_parentesis_check(char *str)
{
	int checker;
	int	i;

	i = -1;
	checker = 0;
	while (str[++i])
	{
		if (str[i] == ')')
			checker = -1;
		else if (str[i] != ')' && checker == -1)
			return (1);
	}
	return (0);
}


static int first_parentesis_check(char *str)
{
	int checker;
	int	i;

	i = -1;
	checker = 0;
	while (str[++i])
	{
		if (str[i] == '(')
			checker = -1;
		else if (str[i] != '(' && checker == -1)
			checker = -2;
		else if (str[i] == '(' && checker == -2)
			return (1);
	}
return (0);
}


static int extract_values(char *str, int *start)
{
	int i;
	int values;

	i = -1;
	values = 0;
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
		{
			(*start) = i;
			while (str[i] != ')')
			{
				values++;
			}
			return (values);
		}
	}
}


int shell_aritmetics(char *str)
{
	int i;
	int	size_of_values;

	i = 0;
	if (first_parentesis_check(str))
		return (1);
	if (second_parentesis_check(str))
		return (1);
	size_of_values = extract_values(str, &i);
//TODO: exacting the value using ft_substr && then parsing that value so it can do aritmetics;
}