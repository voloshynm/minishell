/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/30 19:45:02 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	execute_command(t_shell *m, t_list **parser)
{
	t_command	*c;

	c = ((t_command *)((*parser)->content));
	g_sig_pid = fork();
	if (g_sig_pid == -1)
		return (p_error2("fork", NULL));
	else if (g_sig_pid == 0)
	{
		setup_redirection(c, m);
		execve(c->full_path, c->cmd, NULL);
		exit(p_error2("execve", NULL));
	}
	(*parser) = (*parser)->next;
	return (wait_children(m));
}
/*
**	checking if condition for OR or AND is satisfied
*/
static int	is_bypassing_splitter_or_and(t_command	*c, t_shell *m)
{
	if ((c->last_splitter_token == OR && m->ex_status == 0)
			|| (c->last_splitter_token == AND && m->ex_status != 0))
		return (1);
	return (0);
}
/*
**	to go through elements in case of OR or AND if condition satisfied
*/
static void	advance_after_bypassing_splitter_or_and(t_list **p, t_shell *m)
{
	int	num_pipes;

	if (((t_command *)((*p)->content))->cmd_splitter != PIPE)
		(*p) = (*p)->next;
	else
	{
		num_pipes = count_pipes(m);
		while (num_pipes + 1 > 0)
		{
			(*p) = (*p)->next;
			num_pipes--;
		}
	}
}
/*
**	take the standard output (stdout) of the command on its left
		and send it as the standard input (stdin) to the command on its righ
**	if cmd_splitter == AND && ex_status != 0 (executor succeeded
		at previous command), execute a command
**	if cmd_splitter == OR && ex_status == 0 (executor failed
		at previous command), execute a command
**	if cmd_splitter == | execute a pipe of commands
*/
int	executor_loop(t_shell *m)
{
	t_command	*c;
	t_list		*p;
	int			num_pipes;
	int			cmd_index;

	p = m->parser;
	while (p)
	{
		cmd_index = -1;
		c = ((t_command *)(p->content));
		if (is_bypassing_splitter_or_and(c, m))
			advance_after_bypassing_splitter_or_and(&p, m);
		else if (c->cmd_splitter == PIPE)
		{
			num_pipes = count_pipes(m);
			m->ex_status = execute_pipe(m, &p, num_pipes, cmd_index);
		}
		else
			m->ex_status = execute_command(m, &p);
	}
	return (m->ex_status);
}
