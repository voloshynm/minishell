/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/18 22:37:14 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**	create a list element c of a struct t_command and add it to t_list cmds
*/
static int	init_cmd_struct_add_to_parser_lst(t_command *c, t_shell *m)
{
	t_list	*cmds_lst_el;

	c = ft_calloc(1, sizeof(t_command));
	cmds_lst_el = ft_lstnew(c);
	ft_lstadd_back(&m->parser, cmds_lst_el);
	if (!c || !cmds_lst_el || !m->parser)
		return (p_error(ALLOC_FAILURE, NULL));
	c->infile = STDIN_FILENO;
	c->outfile = STDOUT_FILENO;
	return (OK);
}
static int	get_cmd_len(t_lexer *lexer)
{
	int		len;
	t_lexer	*l;

	l = lexer;
	len = 0;
	while(l->token == WORD)
	{
		len++;
		l = l->next;
	}
	return (len);
}

static int	parse_command(t_command *c, t_lexer *l)
{
	char	**cur_cmd;

	cur_cmd = ft_calloc(1, get_cmd_len(l));
	c->cmd = cur_cmd;
	while (l->token == WORD)
	{
		cur_cmd = l->str;
		l = l->next;
		cur_cmd++;
	}
	return (0);
}

static int	parse_full_path(t_command *c, t_lexer *l, t_shell *m)
{
	// define the actual command, based on the fist token and then
	// check if it is a builtin. Consequently assign a path of the command
	return (0);
}

static int	test_parser(t_shell *m)
{
	// define the actual command, based on the fist token and then
	// check if it is a builtin. Consequently assign a path of the command
	return (0);
}

int	parse_commands(t_shell *m)
{
	t_command	*c;
	char		**cur_cmd;
	t_lexer		*l;

	l = m->lexer;
	while (l)
	{
		if (!init_cmd_struct_add_to_parser_lst(c, m) || !parse_command(c, l))
			return (ALLOC_FAILURE);
		if (!parse_full_path(c, l->str, m))
			return (m->ex_status);
		while (is_token_redir(l->token))
		{
			if (!parse_redirection(&c, l->token, (++l)->str, m))
				return (m->ex_status);
			if ((++l)->token == WORD)
				return (p_error(UNEXPEC_TOKEN, l->str));
		}
		c->cmd_splitter = l->token;
	}
	return (OK);
}
