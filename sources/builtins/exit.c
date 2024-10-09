/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:40 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/09 19:15:15 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(t_shell *m, t_command *c)
{
	int exit_code;
	int i;

	i = 0;
	if (c->cmd[2])
		exit_code = 1;
	else if (c->cmd[1])
	{
		if (c->cmd[1][i] == '+' || c->cmd[1][i] == '-')
			i++;
		while (ft_isdigit(c->cmd[1][i]))
			i++;
		if (c->cmd[1][i] == 0)
			exit_code = ft_atoi(c->cmd[1]) % 256;
		else
			exit_code = 2;
	}
	else 
		exit_code = 0;
	free_all_resources(m);
	exit(exit_code);
}
