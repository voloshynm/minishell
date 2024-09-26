/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/26 01:31:25 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Check if the Child Terminated Normally:
// *Bitwise AND with 0x7F*: checks the lower 7 bits of the status variable
// Normal Termination: If the result is 0, it indicates that the child process
// terminated normally (i.e., it exited without being killed by a signal).
// *Right Shift:((status >> 8) & 0xFF)* The expression status >> 8 shifts
// the bits of status 8 places to the right. The result is then masked with
// 0xFF to ensure we only get the lower 8 bits (the actual exit code).
// *Return Value:* This value represents the exit status of the child process
// (typically in the range of 0 to 255).
// *Return -1* for Abnormal Termination (e.g., it was killed by a signal)
int	return_child_exit(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	else
		return (-1);
}

int	count_pipes(t_shell *m)
{
	t_list		*tmp;
	int			count;
	t_command	*p;

	tmp = m->parser;
	count = 0;
	while (tmp)
	{
		p = ((t_command *)(tmp->content));
		if (p->cmd_splitter == PIPE)
			count++;
		if (p->cmd_splitter != PIPE && count > 0)
			break ;
		tmp = tmp->next;
	}
	return (count);
}

// Waiting for Children: after all children have been created, loop through
// the pids array and call waitpid(pids[i], &status, 0); for each stored PID
// to wait for their termination.
// TODO : in fact I implemented an array of storing all the exit errors for the
// TODO children. You should use this as an input for your signal handling
// TODO when the return is -1 (see return_child_exit)
int	wait_children(t_shell *m, int num_pipes, int pid)
{
	int	i;
	int	status;

	(void) num_pipes;
	i = -1;
		waitpid(pid, &status, 0);
		m->exit_statuses[i + 1] = return_child_exit(status);
	return (0);
}

static int	execute_command(t_shell *m, t_list *parser)
{
	t_command	*p;

	(void)m;
	p = ((t_command *)(parser->content));
	g_sig_pid = fork();
	if (g_sig_pid == -1)
		return (p_error2("fork", NULL));
	else if (g_sig_pid == 0)
	{
		setup_redirection(p, m);
		execve(p->full_path, p->cmd, NULL);
		exit(p_error2("execve", NULL));
	}
	wait_children(m, 0, g_sig_pid);
	return (0);
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

	cmd_index = 0;
	p = m->parser;
	while (p)
	{
		c = ((t_command *)(p->content));
		if (p->next && ((t_command *)(p->next->content))->cmd_splitter == PIPE)
		{
			num_pipes = count_pipes(m);
			m->exit_statuses[0] = execute_pipe(m, p, num_pipes, cmd_index);
			while (num_pipes-- + 1 > 0)
				p = p->next;
		}
		else if ((c->cmd_splitter == OR && m->ex_status != 0)
			|| (c->cmd_splitter == AND && m->ex_status == 0)
			|| c->cmd_splitter == NONE)
		{
			m->exit_statuses[0] = execute_command(m, p);
			p = p->next;
		}
	}
	return (m->exit_statuses[0]);
}
