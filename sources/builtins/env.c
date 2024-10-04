/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:46 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/04 15:31:55 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_shell *m, t_command *c)
{
	if (c->cmd[1] != NULL)
		return (p_error(CMD_TOO_MANY_ARGS, NULL));
	print_envp(m);
	return (0);
}
