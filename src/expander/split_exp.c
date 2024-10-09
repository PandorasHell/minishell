#include "../../minishell.h"

t_cmd_name	*split_exp()
{
	// Esta parte de la expansión splitea el resultado de las variables expandidas sólo si no se enciuentran entre comillas dobles.
	// Por ejeplo: var="file1 file2 file3" ---> echo $var  ---> echo "$var"
	//		salida 1 --> "file1" "file2" "file3"   ||   salida 2 --> "file1 file2 file3"

}