/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:57:12 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/16 20:26:04 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*
	Wait for all child processes to terminate
	Update the exit status of the last child process(*)
	Wait for the next child process
	The assignment exited_pid = wait(&status); is done before the while loop,
	and repeated inside the loop after handling each child process.
	The while loop checks exited_pid > 0, which continues the loop
	as long as wait() successfully returns a child process's PID.
	Handle any errors in wait
	(*)
	Check if the Child Terminated Normally:
	*Bitwise AND with 0x7F*: checks the lower 7 bits of the status variable
	Normal Termination: If the result is 0, it indicates that the child process
	terminated normally (i.e., it exited without being killed by a signal).
	*Right Shift:((status >> 8) & 0xFF)* The expression status >> 8 shifts
	the bits of status 8 places to the right. The result is then masked with
	0xFF to ensure we only get the lower 8 bits (the actual exit code).
	*Return Value:* This value represents the exit status of the child process
	(typically in the range of 0 to 255).
	*Return -1* for Abnormal Termination (e.g., it was killed by a signal)
*/
int	wait_children(t_shell *m)
{
	int	status;
	int	exited_pid;

	exited_pid = wait(&status);
	while (exited_pid > 0)
	{
		if (WIFEXITED(status))
			m->ex_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			m->ex_status = 128 + WTERMSIG(status);
		exited_pid = wait(&status);
	}
	if (exited_pid == -1 && errno != ECHILD)
		return (p_error2("wait", NULL));
	return (m->ex_status);
}

// (c == 'S') Set all pipes
// (c == 'C') Close all pipe file descriptors in child or parent
static int	set_close_pipe(int num_pipes, int pipes[], char c)
{
	int	i;

	i = -1;
	if (c == 'S')
	{
		while (++i < num_pipes)
		{
			if (pipe(pipes + i * 2) == -1)
				return (-1);
		}
	}
	if (c == 'C')
	{
		while (++i < 2 * num_pipes)
			close(pipes[i]);
	}
	return (0);
}

// (1) Child cmd_index: Input redirected from pipe cmd_index - 1
// If not the first command, get input from the previous pipe
// (2) Child cmd_index: Output redirected to pipe cmd_index
// If not the last command, output to the next pipe
// (3) Close pipes
static int	upd_fd(int *cmd_index, int pipes[], t_list **current, int num_pipes)
{
	if (*cmd_index > 0)
	{
		if (dup2(pipes[(*cmd_index - 1) * 2], STDIN_FILENO) == -1)
			return (1);
	}
	if ((*current)->next
		&& ((t_command *)((*current)->content))->cmd_splitter == PIPE)
	{
		if (dup2(pipes[*cmd_index * 2 + 1], STDOUT_FILENO) == -1)
			return (1);
	}
	set_close_pipe(num_pipes, pipes, 'C');
	return (0);
}

// PID Array: created to store the PIDs of each child process as they are forked
// Storing PIDs: Each time call fork(),store the resulting PID in the pids array
int	execute_pipe(t_shell *m, t_list **p, int nm, int i)
{
	int			pi[8192];
	t_command	*c;

	if (set_close_pipe(nm, pi, 'S') == -1)
		return (p_error2("pipe", NULL));
	while ((*p) && ++i < nm + 1)
	{
		c = (t_command *)((*p)->content);
		g_sig_pid = fork();
		if (g_sig_pid == -1)
			return (p_error2("fork", NULL));
		if (g_sig_pid == 0)
		{
			if (is_inv_c_pipe(m, p) || upd_fd(&i, pi, p, nm) || set_redir(c, m))
				exit(1);
			if (is_builtin(c))
				exit(run_builtin(m, p, (t_command *)((*p)->content)));
			execve(c->full_path, c->cmd, NULL);
			exit(1);
		}
		*p = (*p)->next;
	}
	set_close_pipe(nm, pi, 'C');
	restore_and_close_files(c, m);
	return (wait_children(m));
}
