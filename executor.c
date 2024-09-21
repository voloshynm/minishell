/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/21 11:59:30 by sandre-a         ###   ########.fr       */
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

int execute(t_shell *m)
{
    pid_t       pid;
    int         status;
    t_command   *p;

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
        if ((status & 0x7F) == 0)
            return ((status >> 8) & 0xFF);
        else
            return (-1);
    }
    else
        return (-1);
    return (0);
}

int execute_pipe(t_shell *m)
{
    pid_t       pid;
    int         status;
    t_command   *p;

	if (pipe(m->pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    p = ((t_command *)(m->parser->content));
    pid = fork();
    if (pid == 0)
    {
		close(m->pipefd[0]); // Close the read end of the pipe
        dup2(m->pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(m->pipefd[1]); // Close the original write end of the pipe
        execve(p->full_path, p->cmd, NULL);
        exit(127);
    }
    else if (pid > 0)
    {
		close(m->pipefd[1]); // Close the write end of the pipe
        dup2(m->pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(m->pipefd[0]); // Close the original read end of the pipe
        waitpid(pid, &status, 0);
        if ((status & 0x7F) == 0)
            return ((status >> 8) & 0xFF);
        else
            return (-1);
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
**	if cmd_splitter == AND && ex_status != 0 (executor succeeded
		at previous command), execute a command
*/
int	executor_loop(t_shell *m)
{
	t_command	*p;

	while (m->parser)
	{
		p = ((t_command *)(m->parser->content));
		if (p->cmd_splitter == PIPE)
//			execute_pipe(m);
			execute(m);
		else if ((p->cmd_splitter == OR && m->ex_status != 0)
				|| (p->cmd_splitter == AND && m->ex_status == 0)
				|| p->cmd_splitter == NONE)
			execute(m);
		m->parser = m->parser->next;
	}
	return (0);
}