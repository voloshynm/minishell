/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:41:20 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/16 20:26:48 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	function to read into heredoc
*/
static void	heredoc_readline(const char *delimiter, int tmp_fd)
{
	char	*line;

	g_sig_pid = -255;
	while (g_sig_pid == -255)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "warning: heredoc delim by EOF (wanted `", 40);
			write(STDOUT_FILENO, delimiter, ft_strlen(delimiter));
			write(STDOUT_FILENO, "')\n", 3);
			break ;
		}
		if (g_sig_pid == 1
			|| (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0))
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
}

/*
**	create a temp file with a name /tmp/heredoc_tmp_<tmp_pid>
**	launch heredoc_readline() which will record input into the temp file
**	close the file in write mode and reopen it in read-only mode
**	free not needed names of the file (strings)
**	return the file descriptor of this file
*/
static int	handle_heredoc(const char *delimiter, t_shell *m)
{
	int		tmp_fd;
	char	*tmp_filename;
	char	*tmp_pid;

	tmp_pid = ft_itoa(m->pid);
	tmp_filename = ft_strjoin("/tmp/heredoc_tmp_", tmp_pid);
	free(tmp_pid);
	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (p_error(TMP_FILE_CREATION_ERR, NULL));
	signal(SIGQUIT, SIG_IGN);
	heredoc_readline(delimiter, tmp_fd);
	signal(SIGQUIT, SIG_DFL);
	close(tmp_fd);
	if (g_sig_pid != -255)
		return (0 - g_sig_pid - 129);
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd < 0)
		return (p_error(TMP_FILE_CREATION_ERR, NULL));
	free(tmp_filename);
	return (tmp_fd);
}

/*
**	open proper infile or outfile depending on the redirection token type
*/
int	parse_redir(t_command *c, t_token token, char *filename, t_shell *m)
{
	if (token == IN)
		c->infile = open(filename, O_RDONLY);
	else if (token == OUT)
		c->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token == APPEND)
		c->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token == HEREDOC)
		c->infile = handle_heredoc(filename, m);
	if (c->infile == -1 || c->outfile == -1)
	{
		perror(" ");
		return (1);
	}
	else if (c->infile < 0)
		return (0 - c->infile);
	return (0);
}

/*
**	// Redirect input if infile is set and not STDIN
	if (c->infile != STDIN_FILENO)
	Redirect output if outfile is set and not STDOUT
	if (c->outfile != STDOUT_FILENO)
*/
int	set_redir(t_command *c, t_shell *m)
{
	if (c->infile != STDIN_FILENO)
	{
		m->pipefd[0] = dup(STDIN_FILENO);
		if (m->pipefd[0] < 0)
			return (errno);
		if (dup2(c->infile, STDIN_FILENO) < 0)
			return (errno);
	}
	if (c->outfile != STDOUT_FILENO)
	{
		m->pipefd[1] = dup(STDOUT_FILENO);
		if (m->pipefd[1] < 0)
			return (errno);
		if (dup2(c->outfile, STDOUT_FILENO) < 0)
			return (errno);
	}
	return (0);
}

/*
**	// Restore stdin from pipefd[0] and close infile if it was redirected
**	// Restore stdout from pipefd[1] and close outfile if it was redirected
*/
void	restore_and_close_files(t_command *c, t_shell *m)
{
	if (c->infile != STDIN_FILENO)
	{
		dup2(m->pipefd[0], STDIN_FILENO);
		close(m->pipefd[0]);
		if (c->infile != -1)
			close(c->infile);
	}
	if (c->outfile != STDOUT_FILENO)
	{
		dup2(m->pipefd[1], STDOUT_FILENO);
		close(m->pipefd[1]);
		if (c->outfile != -1)
			close(c->outfile);
	}
}
