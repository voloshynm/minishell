/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:45:16 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/08 19:36:23 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	1. By default, print a newline
	2. Check for the '-n' flag, which may appear multiple times
	3. Write the remaining arguments
	4. Write a newline unless '-n' was used
*/
int	echo(char **cmd)
{
	int	print_new_line;
	int	i;

	print_new_line = 1;
	i = 0;
	while (cmd[++i] && strcmp(cmd[i], "-n") == 0)
		print_new_line = 0;
	while (cmd[i])
	{
		write(STDOUT_FILENO, cmd[i], strlen(cmd[i]));
		if (cmd[++i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (print_new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
