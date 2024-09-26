/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/26 23:02:27 by mvoloshy         ###   ########.fr       */
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
int	wait_children(t_shell *m, int num_pipes, int pids[])
{
	int i;
	int	status;

	i = -1;
	while (++i < num_pipes + 1)
	{
		waitpid(pids[i], &status, 0);
		m->exit_statuses[i + 1] = return_child_exit(status);
	}
	return (0);
}

int	execute_command(t_shell *m, t_list **p)
{
	pid_t		pids[1];
	t_command	*c;

	(void)m;
	c = ((t_command *)((*p)->content));
	pids[0] = fork();
	if (pids[0] == -1)
		return (p_error2("fork", NULL));
	else if (pids[0] == 0)
	{
		setup_redirection(c, m);
		execve(c->full_path, c->cmd, NULL);
		exit(p_error2("execve", NULL));
	}
	wait_children(m, 0, pids);
	(*p) = (*p)->next;
	return (0);
}
int	is_failed_splitter_or_and(t_command	*c, t_shell *m)
{
	if ((c->last_splitter_token == OR && m->ex_status == 0)
			|| (c->last_splitter_token == AND && m->ex_status != 0))
		return (1);
	return (0);
}

static void	reset_std_fds(t_shell *m)
{
	// Reset stdout and stdin before executing a non-piped command
	dup2(m->pipefd[1], STDOUT_FILENO);
	dup2(m->pipefd[0], STDIN_FILENO);
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
		cmd_index = 0;
		c = ((t_command *)(p->content));
		if (is_failed_splitter_or_and(c, m))
			p = p->next;	
		else if (c->cmd_splitter == PIPE)
		{
			num_pipes = count_pipes(m);
			printf("num_pipes = %d\n", num_pipes);
			m->exit_statuses[0] = execute_pipe(m, &p, num_pipes, cmd_index);
		}
		else
		{
			reset_std_fds(m);
			m->exit_statuses[0] = execute_command(m, &p);
		}
	}
	return (m->exit_statuses[0]);
}
