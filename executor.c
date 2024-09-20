/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/20 18:32:21 by sandre-a         ###   ########.fr       */
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

int	executor_loop(t_shell *m)
{
	while (m->parser)
	{
		

		m->parser = m->parser->next;
	}
	return (0);
}