/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/09 14:57:05 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_builtin(t_shell *m, t_list **parser, t_command *c)
{
	if (!ft_strcmp(c->cmd[0], "cd"))
		m->ex_status = cd(m, c->cmd);
	else if (!ft_strcmp(c->cmd[0], "pwd"))
		m->ex_status = pwd();
	else if (!ft_strcmp(c->cmd[0], "echo"))
		m->ex_status = echo(c->cmd);
	else if (!ft_strcmp(c->cmd[0], "export"))
		m->ex_status = export(m, c);
	else if (!ft_strcmp(c->cmd[0], "env"))
		m->ex_status = export(m, c);
	else if (!ft_strcmp(c->cmd[0], "unset"))
		m->ex_status = unset(m, c);
	else if (!ft_strcmp(c->cmd[0], "exit"))
		exit_shell(m);
	restore_and_close_files(c, m);
	(*parser) = (*parser)->next;
	return (m->ex_status);
}

int	execute_command(t_shell *m, t_list **parser)
{
	t_command	*c;

	c = ((t_command *)((*parser)->content));
	setup_redirection(c, m);
	if (is_builtin(c, m))
		return (run_builtin(m, parser, c));
	if (c->full_path == NULL)
	{
		(*parser) = (*parser)->next;
		return (p_error(CMD_NOT_EXIST, c->cmd[0]));
	}
	g_sig_pid = fork();
	if (g_sig_pid == -1)
		return (p_error2("fork", NULL));
	else if (g_sig_pid == 0)
	{
		execve(c->full_path, c->cmd, NULL);
		exit(p_error2("execve", NULL));
	}
	restore_and_close_files(c, m);
	(*parser) = (*parser)->next;
	return (wait_children(m));
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

int	is_invalid_command_in_pipe(t_shell *m, t_list **p, int num_pipes)
{
	t_list		*start;
	t_command	*c;
	bool		is_invalid;

	start = *p;
	is_invalid = false;
	while (num_pipes + 1)
	{
		c = ((t_command *)((*p)->content));
		if (c->full_path == NULL && !is_builtin(c, m))
		{
			if (!is_invalid)
				printf("%s: command not found\n", c->cmd[0]);
			is_invalid = true;
		}
		*p = (*p)->next;
		num_pipes--;
	}
	if (is_invalid)
		m->ex_status = CMD_NOT_EXIST;
	else
		*p = start;
	return (is_invalid);
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
		if ((c->last_splitter_token == OR && m->ex_status == 0)
			|| (c->last_splitter_token == AND && m->ex_status != 0))
			advance_after_bypassing_splitter_or_and(&p, m);
		else if (c->cmd_splitter == PIPE)
		{
			num_pipes = count_pipes(m);
			if (!is_invalid_command_in_pipe(m, &p, num_pipes))
				m->ex_status = execute_pipe(m, &p, num_pipes, cmd_index);
		}
		else
			m->ex_status = execute_command(m, &p);
	}
	return (m->ex_status);
}
