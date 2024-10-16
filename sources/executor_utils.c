/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:12:31 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/16 20:27:53 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_inv_c_pipe(t_shell *m, t_list **p)
{
	t_command	*c;
	bool		is_invalid;

	is_invalid = false;
	c = ((t_command *)((*p)->content));
	if (c->full_path == NULL && !is_builtin(c))
	{
		if (!is_invalid)
			printf("%s: command not found\n", c->cmd[0]);
		is_invalid = true;
	}
	if (*p && (*p)->next && is_invalid)
		*p = (*p)->next;
	if (is_invalid)
		m->ex_status = CMD_NOT_EXIST;
	return (is_invalid);
}