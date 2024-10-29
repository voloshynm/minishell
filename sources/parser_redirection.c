/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:41:20 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/29 18:56:47 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	function to read into heredoc
*/
static void	heredoc_readline(char *delim, int tmp_fd, char **envp, int is_sq)
{
	char	*line;

	g_sig_pid = -255;
	while (g_sig_pid == -255)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "warning: heredoc delim by EOF (wanted `", 40);
			write(STDOUT_FILENO, delim, ft_strlen(delim));
			write(STDOUT_FILENO, "')\n", 3);
			break ;
		}
		if (g_sig_pid == 130
			|| (line && ft_strncmp(line, delim, ft_strlen(delim)) == 0))
		{
			free(line);
			break ;
		}
		if (!is_sq && ft_strchr(line, '$'))
			process_env_arg(&line, &envp);
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
static int	handle_heredoc(char *delimiter, t_shell *m, int is_squote)
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
	heredoc_readline(delimiter, tmp_fd, m->envp, is_squote);
	signal(SIGQUIT, SIG_DFL);
	close(tmp_fd);
	tmp_fd = open(tmp_filename, O_RDONLY);
	free(tmp_filename);
	if (g_sig_pid != -255)
		return (0 - g_sig_pid);
	if (tmp_fd < 0)
		return (p_error(TMP_FILE_CREATION_ERR, NULL));
	return (tmp_fd);
}

/*
**	open proper infile or outfile depending on the redirection token type
*/
int	parse_redir(t_command *c, t_token token, t_lexer *l, t_shell *m)
{
	char	*filename;
	int		is_squote;

	is_squote = 0;
	if (l->q_type == '\'')
		is_squote = 1;
	l->str = process_str(l->str, l->q_type);
	filename = l->str;
	if (token == IN)
		c->infile = open(filename, O_RDONLY);
	else if (token == OUT)
		c->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token == APPEND)
		c->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token == HEREDOC)
		c->infile = handle_heredoc(filename, m, is_squote);
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
		if (m->pipefd[0] != -1 && m->pipefd[0] != -255)
			dup2(m->pipefd[0], STDIN_FILENO);
		if (m->pipefd[0] != -1 && m->pipefd[0] != -255)
			close(m->pipefd[0]);
		if (c->infile != -1)
			close(c->infile);
	}
	if (c->outfile != STDOUT_FILENO)
	{
		if (m->pipefd[1] != -1 && m->pipefd[1] != -255)
			dup2(m->pipefd[1], STDOUT_FILENO);
		if (m->pipefd[1] != -1 && m->pipefd[1] != -255)
			close(m->pipefd[1]);
		if (c->outfile != -1)
			close(c->outfile);
	}
}
