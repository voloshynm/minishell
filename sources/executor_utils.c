/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:12:31 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/28 21:40:17 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_inv_c_pipe(t_shell *m, t_list **p)
{
	t_command	*c;
	bool		is_invalid;

	is_invalid = false;
	c = ((t_command *)((*p)->content));
	if (!c->cmd[0] || !c->cmd[0][0])
		return (1);
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

int	get_cmd_len(t_lexer *lexer)
{
	int		len;
	int		redir;
	t_lexer	*l;

	l = lexer;
	len = 0;
	redir = 0;
	while (l && !is_token_pipish(l))
	{
		if (is_token_redir(l))
			redir += 2;
		len++;
		l = l->next;
	}
	return (len);
}