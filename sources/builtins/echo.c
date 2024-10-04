/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/10/04 17:26:33 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
^ bool is initialized to false, we invert the logic to print or not \n
*/
int	echo(char **arg)
{
	int		i;
	bool	newline;
	int		j;
	char	**cmd;

	cmd = arg;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i++][j] != '\0')
			break ;
		newline = true;
	}
	while (cmd[i++])
	{
		ft_putstr_fd(cmd[i - 1], 1);
		if (cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (!newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
