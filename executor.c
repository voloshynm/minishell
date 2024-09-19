/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/19 22:15:41 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	excecute(t_shell *m)
{
	pid_t		pid;
	int			status;
	t_command	*p;

	p = ((t_command *)(m->parser->content));
	pid = fork();
	if (pid == 0) // Child process
	{
		execve(p->full_path, p->cmd, NULL);
		perror("execve failed");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork failed");
		return (-1);
	}
	return (1);
}
