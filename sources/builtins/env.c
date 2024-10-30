/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:46 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/30 23:30:54 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_shell *m, t_command *c)
{
	char	**v;

	if (c->cmd[1] != NULL)
		return (p_error(CMD_TOO_MANY_ARGS, NULL));
	v = m->envp;
	while (*v)
	{
		if (ft_strpbrk(*v, "="))
			printf("%s\n", *(v));
		v++;
	}
	return (0);
}
