/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/20 12:21:00 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	execute(t_shell *m)
{
	pid_t		pid;
	int			status;
	t_command	*p;

	p = ((t_command *)(m->parser->content));
	pid = fork();
	if (pid == 0)
	{ // Child process
		execve(p->full_path, p->cmd, NULL);
		perror("execve failed");
		exit(127); // Common convention: 127 indicates command not found
	}
	else if (pid > 0)
	{ // Parent process
		waitpid(pid, &status, 0);
		if ((status & 0x7F) == 0)
		{                                        
			int exit_code = (status >> 8) & 0xFF;
			//printf("Child exited with status: %d\n", exit_code);
			return (exit_code); // Return the child's exit code
		}
		else
		{
			//printf("Child was terminated by signal: %d\n", status & 0x7F);
			return (-1); // Indicate an abnormal termination
		}
	}
	else
	{
		perror("fork failed");
		return (-1);
	}
	return (0);
}
