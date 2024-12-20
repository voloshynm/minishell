/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:51 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/16 02:10:32 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Prints the error
	Returns the error
*/
int	p_error(int err_id, void *arg)
{
	(void)arg;
	if (err_id == ALLOC_FAILURE)
		write(2, "Error: Memory allocation failure\n", 33);
	else if (err_id == UNEXPEC_TOKEN)
		write(2, "Syntax error near unexpected token\n", 35);
	else if (err_id == QUOTE_ERROR)
		write(2, "Error: Invalid quote usage\n", 27);
	else if (err_id == CMD_NOT_EXIST)
		write(2, "Error: command not found\n", 25);
	else if (err_id == CMD_TOO_MANY_ARGS)
		write(2, "Error: cd: too many arguments\n", 30);
	else if (err_id == CMD_TOO_FEW_ARGS)
		write(2, "Error: cd: required one argument\n", 33);
	else if (err_id == ENV_VAR_NOT_EXIST)
		write(2, "Error: Not able to get timestamp error\n", 39);
	else if (err_id == TMP_FILE_CREATION_ERR)
		write(2, "Error: Error creating temporary file\n", 37);
	else if (err_id == INVAL_ENV_VAR)
		write(2, "Error: not a valid identifier\n", 30);
	else if (err_id == DUP2_ERR)
		perror("dup2");
	else if (err_id == PERM_DENIED)
		write(2, "Error: Permission denied\n", 25);
	return (err_id);
}

/*
**	updated function to use perror
**	returns actual error id through errno
*/
int	p_error2(char *str, void *arg)
{
	(void)arg;
	perror(str);
	return (errno);
}
