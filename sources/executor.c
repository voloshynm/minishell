/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/18 16:31:19 by sandre-a         ###   ########.fr       */
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
		exit_shell(m, c);
	restore_and_close_files(c, m);
	(*parser) = (*parser)->next;
	return (m->ex_status);
}

static int	is_dir_or_file(t_command *c)
{
	struct stat	file_stat;
	DIR			*dir;

	file_stat.st_mode = 0;
	stat(c->cmd[0], &file_stat);
	dir = opendir(c->cmd[0]);
	if (dir && (!ft_strncmp(c->cmd[0], "./", 2) || !ft_strncmp(c->cmd[0], "/",
				1)))
	{
		closedir(dir);
		return (write(2, "Error: Is a directory\n", 22), 126);
	}
	else if (!S_ISDIR(file_stat.st_mode) && !ft_strncmp(c->cmd[0], "./", 2))
	{
		if (access(c->cmd[0], F_OK) == 0)
			return (write(2, "Error: Permission denied\n", 25), 126);
		else
			return (write(2, "Error: No such file or directory\n", 33), 127);
	}
	else if (!S_ISDIR(file_stat.st_mode) && access(c->cmd[0], X_OK) < 0
		&& (!ft_strncmp(c->cmd[0], "/", 1)))
		return (write(2, "Error: No such file or directory\n", 33), 127);
	return (p_error(CMD_NOT_EXIST, NULL));
}

int	execute_command(t_shell *m, t_list **parser)
{
	t_command	*c;

	c = ((t_command *)((*parser)->content));
	set_redir(c, m);
	if (is_builtin(c))
		return (run_builtin(m, parser, c));
	if (c->full_path == NULL)
	{
		(*parser) = (*parser)->next;
		return (is_dir_or_file(c));
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

	p = m->parser;
	while (p)
	{
		c = ((t_command *)(p->content));
		if ((c->last_splitter_token == OR && m->ex_status == 0)
			|| (c->last_splitter_token == AND && m->ex_status != 0))
			advance_after_bypassing_splitter_or_and(&p, m);
		else if (c->cmd_splitter == PIPE)
		{
			num_pipes = count_pipes(m);
			m->ex_status = execute_pipe(m, &p, num_pipes, -1);
		}
		else if (c->infile >= 0 && c->outfile >= 0)
			m->ex_status = execute_command(m, &p);
		else
			p = p->next;
	}
	return (m->ex_status);
}
