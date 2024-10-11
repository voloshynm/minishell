/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:40 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/11 18:23:36 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(t_shell *m, t_command *c)
{
	int	i;

	i = 0;
	if (c->cmd[2])
	{
		write (2, " too many arguments", 19);
		exit(1);
	}
	else if (c->cmd[1])
	{
		if (c->cmd[1][i] == '+' || c->cmd[1][i] == '-')
			i++;
		while (ft_isdigit(c->cmd[1][i]))
			i++;
		if (c->cmd[1][i] == 0)
			exit(ft_atoi(c->cmd[1]) % 256);
		else
		{
			write (2, " numeric argument required", 26);
			exit(2);
		}
	}
	free_all_resources(m);
	exit(0);
}
