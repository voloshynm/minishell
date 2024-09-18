/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/18 15:19:52 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int handle_heredoc(const char *delimiter, t_shell *m)
{
	char	*line;
	int		tmp_fd;
	char	*tmp_filename;

	tmp_filename = ft_strjoin("/tmp/heredoc_tmp_", ft_itoa(m->pid)) ;  // You could use `getpid()` to ensure unique filenames
	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return(p_error("Error creating temporary file", NULL));
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd < 0)
		return(p_error("Error re-opening temporary file", NULL));
	return (tmp_fd);
}


int	parse_redirection(t_command	*c, t_token token, char *filename, t_shell *m)
{
	if (token == IN)
	{
		c->infile = open(filename, O_RDONLY);
		if (c->infile < 0)
			return(p_error(RED_IN_ERR, NULL));
	}
	else if (token == OUT)
	{
		c->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (c->outfile < 0)
			return(p_error(RED_OUT_ERR, NULL));
	}
	else if (token == APPEND)
	{
		c->outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (c->outfile < 0)
			return(p_error(RED_APPEND_ERR, NULL));
	}
	else if (token == HEREDOC)
	{
		c->infile = handle_heredoc(filename, m);
		if (c->infile < 0)
			return(p_error(RED_HEREDOC_ERR, NULL));
	}
}


int		parse_commands(t_shell *m)
{
	t_command	*c;
	char		**cur_cmd;
	t_lexer		*l;
	t_list		*cmds_lst_el;

	l = m->lexer;
	while (l)
	{
		c = ft_calloc(1, sizeof(t_command));
		cmds_lst_el = ft_lstnew(c);
		ft_lstadd_back(&m->parser, cmds_lst_el);	// create a list element c of a struct t_command and add it to t_list cmds
		if (!c || !cmds_lst_el || !m->parser)
			return (p_error(ALLOC_FAILURE, NULL));
//		parse_full_path(c, (*l)->str);		// define the actual command, based on the fist token and then check if it is a builtin. Consequently assign a path of the command
		cur_cmd = c->cmd;						// ensure we don't lose the initial pointer during iteration and use a temp one instead
		while (l->token == WORD)
		{
			cur_cmd = l->str;
			l = l->next;
			cur_cmd++;
		}
		c->infile = STDIN_FILENO;
		c->outfile = STDOUT_FILENO;
		while (is_token_redir(l->token))
		{
			if (!((l + 2)) && is_token_redir((l + 2)->token))
			{
				l += 2;
				continue ;
			}
			else
				parse_redirection(&c, l->token, (l++)->str, m);		// process the type of redirection and thus record into infile & outfile
		}
		c->cmd_splitter = l->token;
	}
	return (OK);
}
