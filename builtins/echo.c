/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/09/25 15:04:40 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **args)
{
	int	i;
	int	newline;
	int	j;

	(void) argc;
	i = 0;
	newline = 1;
	while (args[++i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		newline = 0;
	}
	while (args[i++])
	{
		ft_putstr_fd(args[i - 1], 1);
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
