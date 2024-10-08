/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/10/06 21:52:27 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo(char **arg)
{
	int		i;
	int		newline;
	int		j;
	char	**cmd;

	cmd = arg;
	i = 0;
	newline = 1;
	while (cmd[++i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
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
