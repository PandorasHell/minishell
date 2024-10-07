#include "../../minishell.h"

char	*quote_remove(char *word)
{
	// En esta función la idea es eliminar todas las comillas que no sean parte de un string.
	// Como ejemplos:
	// echo "hola :)"   ---> Elimina las comillas dobles, tanto al principio como al final.
	// echo "'adios :('" ---> Elimina las comillas dobles, epro no las simples.
	// var="'fids pe'"; echo $var ---> Igual que antes, elimina las dobles pero no las simples.

}