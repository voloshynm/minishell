/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/23 22:32:38 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int	execute(t_shell *m)
// {
// 	pid_t		pid;
// 	int			status;
// 	t_command	*p;

// 	p = ((t_command *)(m->parser->content));
// 	pid = fork();
// 	if (pid == 0)
// 	{ // Child process
// 		m->ex_status = execve(p->full_path, p->cmd, NULL);
// 		perror("execve failed");
// 		exit(127); // Common convention: 127 indicates command not found
// 	}
// 	else if (pid > 0)
// 	{ // Parent process
// 		waitpid(pid, &status, 0);
// 		if ((status & 0x7F) == 0)
// 		{
// 			int exit_code = (status >> 8) & 0xFF;
// 			//printf("Child exited with status: %d\n", exit_code);
// 			return (exit_code); // Return the child's exit code
// 		}
// 		else
// 		{
// 			//printf("Child was terminated by signal: %d\n", status & 0x7F);
// 			return (-1); // Indicate an abnormal termination
// 		}
// 	}
// 	else
// 	{
// 		perror("fork failed");
// 		return (-1);
// 	}
// 	return (0);
// }

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int	count_pipes(t_shell *m)
{
	t_list		*tmp;
	int			count;
	t_command	*p;
	
	tmp = m->parser;
	p = ((t_command *)(m->parser->content));
	count = 0;
	while (tmp)
	{
		if (p->cmd_splitter == PIPE)
			count++;
		if (p->cmd_splitter != PIPE && count > 0)
			break ;
		tmp = tmp->next;
	}
	return (count);
}

static void	handle_fds_child(int pipefd[2][2], int i, int num_pipes)
{
	if (i != 0) // If not the first command, get input from previous pipe
	{
		dup2(pipefd[(i + 1) % 2][0], STDIN_FILENO);
		close(pipefd[(i + 1) % 2][0]);
		close(pipefd[(i + 1) % 2][1]);
	}
	if (i < num_pipes) // If not the last command, set output to current pipe
	{
		close(pipefd[i % 2][0]);
		dup2(pipefd[i % 2][1], STDOUT_FILENO);
		close(pipefd[i % 2][1]);
	}
}

static void	handle_fds_parent(int pipefd[2][2], int i, int num_pipes)
{
	(void) num_pipes;
	if (i != 0)  // Parent: Close the pipes of the previous command
	{
		close(pipefd[(i + 1) % 2][0]);
		close(pipefd[(i + 1) % 2][1]);
	}
}

static int	return_child_exit(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	else
		return (-1);
}

int	execute_pipe(t_shell *m)
{
	pid_t		pid;
	int			status;
	int			i;
	int			num_pipes;
	int			pipefd[2][2]; // Two sets of pipe file descriptors for alternating between commands
	t_command	*p;

	num_pipes = count_pipes(m); // Count the number of pipes needed (number of pipes)
	i = -1;
	while (++i <= num_pipes)
	{
		p = ((t_command *)(m->parser->content));
		if (i < num_pipes) // Create a new pipe except for the last command
		{
			if (pipe(pipefd[i % 2]) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == 0)
		{
			handle_fds_child(pipefd, i, num_pipes);
			execve(p->full_path, p->cmd, NULL);
			perror("execve failed");
			exit(127);
		}
		else if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		handle_fds_parent(pipefd, i, num_pipes);
		if (m->parser->next != NULL)
			m->parser = m->parser->next; // Move to the next command in the pipeline
		waitpid(-1, &status, 0);
	}
	return(return_child_exit(status));
}

int	execute_command(t_shell *m)
{
	pid_t		pid;
	int			status;
	t_command	*p;

	p = ((t_command *)(m->parser->content));
	pid = fork();
	if (pid == 0)
	{
		execve(p->full_path, p->cmd, NULL);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return(return_child_exit(status));
	}
	else
		return (-1);
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
	t_command *p;

	while (m->parser)
	{
		p = ((t_command *)(m->parser->content));
		if (p->cmd_splitter == PIPE)
			execute_pipe(m);
		if ((p->cmd_splitter == OR && m->ex_status != 0)
			|| (p->cmd_splitter == AND && m->ex_status == 0)
			|| p->cmd_splitter == NONE)
			execute_command(m);
		m->parser = m->parser->next;
	}
	return (0);
}
