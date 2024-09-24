/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/24 21:10:51 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// OPTIMIZATION WORK
// int	handle_pipes(int num_pipes, int pipes[2 * num_pipes], char c)
// {
// 	int		i;

// 	i = -1;
// 	if (c = 'S')
// 	{
// 		while (++i < num_pipes)
// 		{
// 			if (pipe(pipes + i * 2) == -1)
// 			{
// 				perror("pipe");
// 				return -1;
// 			}
// 		}
// 	}
// 	else if (c = 'C')
// 	{
// 		while (++i < 2 * num_pipes) // Close all pipe file descriptors in child
// 			close(pipes[i]);
// 	}
// 	return (0);
// }

// int execute_pipe(t_shell *m, t_list *parser, int num_pipes)
// {
// 	t_list		*current;
// 	t_command	*p;
// 	int			pipes[2 * num_pipes]; // Array to hold pipe file descriptors
// 	int			i;
// 	int			command_index;

// 	if (!handle_pipes(num_pipes, pipes, 'S'))
// 		return (-1);
// 	command_index = 0;
// 	current = parser;
// 	while (current)
// 	{
// 		p = (t_command *)(current->content);
// 		pid_t pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			return -1;
// 		}
// 		if (pid == 0) // Child process
// 		{
// 			if (command_index > 0) // If not the first command, get input from the previous pipe
// 			{
// 				if (dup2(pipes[(command_index - 1) * 2], STDIN_FILENO) == -1)
// 				{
// 					perror("dup2");
// 					exit(1);
// 				}
// 			}	
// 			if (current->next) // If not the last command, output to the next pipe
// 			{
// 				if (dup2(pipes[command_index * 2 + 1], STDOUT_FILENO) == -1)
// 				{
// 					perror("dup2");
// 					exit(1);
// 				}
// 			}
// 			handle_pipes(num_pipes, pipes, 'S');
// 			execve(p->full_path, p->cmd, NULL);
// 			perror("execve"); // If execve fails
// 			exit(127);
// 		}
// 		current = current->next; // Move to the next command
// 		command_index++;
// 	}
// 	handle_pipes(num_pipes, pipes, 'S'); // Parent process: close all pipe file descriptors

// 	// Wait for all child processes
// 	int status;
// 	i = -1;
// 	while (++i < command_index)
// 	{
// 		wait(&status);
// 		printf("***DEBUG*** Parent: Child process %d exited with status %d\n", i, WEXITSTATUS(status));
// 	}
// 	return return_child_exit(status); // Assuming return_child_exit handles status properly
// }

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

static int	return_child_exit(int status)
{
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	else
		return (-1);
}

int execute_pipe(t_shell *m, t_list *parser, int num_pipes)
{
	t_list *current = parser;
	int pipes[2 * num_pipes]; // Array to hold pipe file descriptors
	int i = 0;

	(void)m;
	// Create all pipes
	while (i < num_pipes)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			perror("pipe");
			return -1;
		}
		printf("***DEBUG*** Pipe %d created\n", i);
		i++;
	}

	int command_index = 0;
	while (current)
	{
		t_command *p = (t_command *)(current->content);
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			return -1;
		}

		if (pid == 0) // Child process
		{
			// If not the first command, get input from the previous pipe
			if (command_index > 0)
			{
				if (dup2(pipes[(command_index - 1) * 2], STDIN_FILENO) == -1)
				{
					perror("dup2");
					exit(1);
				}
				printf("***DEBUG*** Child %d: Input redirected from pipe %d\n", command_index, command_index - 1);
			}

			// If not the last command, output to the next pipe
			if (current->next)
			{
				if (dup2(pipes[command_index * 2 + 1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(1);
				}
				printf("***DEBUG*** Child %d: Output redirected to pipe %d\n", command_index, command_index);
			}

			// Close all pipe file descriptors in child
			i = 0;
			while (i < 2 * num_pipes)
			{
				close(pipes[i]);
				i++;
			}

			// Execute the command
			printf("***DEBUG*** Child %d: Executing command: %s\n", command_index, p->full_path);
			execve(p->full_path, p->cmd, NULL);
			perror("execve"); // If execve fails
			exit(127);
		}

		current = current->next; // Move to the next command
		command_index++;
	}

	// Parent process: close all pipe file descriptors
	i = -1;
	while (++i < 2 * num_pipes)
	{
		close(pipes[i]);
		printf("***DEBUG*** Parent: Closed pipe %d\n", i);
	}

	// Wait for all child processes
	int status;
	i = 0;
	while (i < command_index)
	{
		wait(&status);
		printf("***DEBUG*** Parent: Child process %d exited with status %d\n", i, WEXITSTATUS(status));
		i++;
	}

	return return_child_exit(status); // Assuming return_child_exit handles status properly
}
int	execute_command(t_shell *m, t_list *parser)
{
	pid_t		pid;
	int			status;
	t_command	*p;

	(void)m;
	p = ((t_command *)(parser->content));
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
	t_command	*p;
	t_command	*p_next;
	t_list		*parser;
	int			num_pipes;

	parser = m->parser;
	while (parser)
	{
		p = ((t_command *)(parser->content));
		if (parser->next)
			p_next = ((t_command *)(parser->next->content));
		if (p_next && p_next->cmd_splitter == PIPE)
		{
			num_pipes = count_pipes(m);
			m->ex_status = execute_pipe(m, parser, num_pipes);
			while (num_pipes-- + 1 > 0)
				parser = parser->next;
		}
		else if ((p->cmd_splitter == OR && m->ex_status != 0)
			|| (p->cmd_splitter == AND && m->ex_status == 0)
			|| p->cmd_splitter == NONE)
		{
			m->ex_status = execute_command(m, parser);
			parser = parser->next;
		}
	}
	return (m->ex_status);
}
