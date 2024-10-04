/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:30 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/04 15:30:19 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_shell *m, t_command *c)
{
	int	i;

	i = 1;
	while (c->cmd[i] != NULL)
	{
		if (rm_from_envp(m, c->cmd[i]))
			return (ALLOC_FAILURE);
		i++;
	}
	return (0);
}
