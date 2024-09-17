#include "includes/minishell.h"

/*
**	Prints the error
	Frees the resources
    Returns the error
*/
int	p_error(int err_id, void **arg_1)
{
	if (err_id == ALLOC_FAILURE)
		printf("Error:\nMemory allocation failure\n");
	else if (err_id == UNEXPEC_TOKEN)
		printf("Error:\nsyntax error near unexpected token `%s'\n", (char *) *arg_1);
	else if (err_id == QUOTE_ERROR)
		printf("Error:\nInvalid quote usage\n");
	else if (err_id == CMD_NOT_EXIST)
		printf("Error:\n%s: command not found\n", (char *) *arg_1);
    else if (err_id == ENV_VAR_NOT_EXIST)
		printf("Error:\nNot able to get timestamp error\n");
	if (err_id == ALLOC_FAILURE || err_id == CMD_NOT_EXIST
		|| err_id == ENV_VAR_NOT_EXIST)
		;
	return (err_id);
}