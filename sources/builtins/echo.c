/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:45:16 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/08 18:29:36 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
^ bool is initialized to false, we invert the logic to print or not \n
*/
int	echo(char **cmd)
{
	int		i;
	int		newline;
	int		j;

	i = 1;
	newline = false;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		newline = 0;
	}
	while (cmd[i++])
	{
		ft_putstr_fd(cmd[i - 1], 1);
		if (cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
