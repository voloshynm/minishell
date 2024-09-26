/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:51 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/26 12:21:00 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**	Prints the error
	Frees the resources
	Returns the error
*/
int	p_error(int err_id, void *arg)
{
	if (err_id == ALLOC_FAILURE)
		printf("Error: Memory allocation failure\n");
	else if (err_id == UNEXPEC_TOKEN)
		printf("Syntax error near unexpected token `%s'\n", (char *) arg);
	else if (err_id == QUOTE_ERROR)
		printf("Error: Invalid quote usage\n");
	else if (err_id == CMD_NOT_EXIST)
		printf("Error: %s: command not found\n", (char *) arg);
	else if (err_id == ENV_VAR_NOT_EXIST)
		printf("Error: Not able to get timestamp error\n");
	else if (err_id == RED_IN_ERR)
		printf("Error: Error opening input file\n");
	else if (err_id == RED_OUT_ERR)
		printf("Error: Error opening output file\n");
	else if (err_id == RED_APPEND_ERR)
		printf("Error: Error opening output file in append mode\n");
	else if (err_id == RED_HEREDOC_ERR)
		printf("Error: Error opening heredoc file\n");
	else if (err_id == TMP_FILE_CREATION_ERR)
		printf("Error: Error creating temporary file\n");
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

/*
^Checks for simple input errors before splitting into tokens,
^Examples: <> <<< |& etc... 
*/
int	input_error(char *input)
{
	char	token_type;

	while (1)
	{
		input = ft_strpbrk(input, "|&<>");
		if (input)
			token_type = *input;
		if (!input)
			break ;
		if (*(++input) == ' ' || *input == '\t')
		{
			while (*input == ' ' || (*input == '\t' && *input))
				input++;
			if (*input == token_type)
				return (p_error(2, &token_type));
		}
	}
	return (0);
}
