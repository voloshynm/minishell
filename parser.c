/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/19 22:21:57 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**	create a list element c of a struct t_command and add it to t_list cmds
*/
static int	init_cmd_struct_add_to_parser_lst(t_command **c, t_shell *m)
{
	t_list	*cmds_lst_el;

	*c = ft_calloc(1, sizeof(t_command));
	cmds_lst_el = ft_lstnew(*c);
	ft_lstadd_back(&m->parser, cmds_lst_el);
	if (!c || !cmds_lst_el || !m->parser)
		return (p_error(ALLOC_FAILURE, NULL));
	(*c)->infile = STDIN_FILENO;
	(*c)->outfile = STDOUT_FILENO;
	return (OK);
}
static int	get_cmd_len(t_lexer *lexer)
{
	int		len;
	t_lexer	*l;

	l = lexer;
	len = 0;
	while (l && l->token == WORD)
	{
		len++;
		l = l->next;
	}
	return (len);
}

static int	parse_command(t_command *c, t_lexer **l)
{
	char	**cur_cmd;

	cur_cmd = ft_calloc(get_cmd_len(*l) + 1, sizeof(char *));
	c->cmd = cur_cmd;
	while (*l && (*l)->token == WORD)
	{
		*cur_cmd = (*l)->str;
		*l = (*l)->next;
		cur_cmd++;
	}
	*cur_cmd = NULL;
	return (0);
}

static int	parse_full_path(t_command *c, t_shell *m)
{
	char		*temp;
	t_command	*p;

	p = ((t_command *)(m->parser->content));
	p->full_path = NULL;
	is_builtin(m);
	if (!p->full_path)
		is_bin(m);
	if (p->full_path)
	{
		temp = ft_strjoin(p->full_path, "/");
		p->full_path = ft_strjoin(temp, p->cmd[0]);
		free(temp);
	}
	else
		printf("%s: command not found\n", p->cmd[0]);
	excecute(m);
	(void)c;
	return (0);
}

static int	test_parser(t_shell *m)
{
	t_command	*test;

	while ((t_command *)(m->parser))
	{
		test = (t_command *)(m->parser->content);
		while (*test->cmd)
		{
			// printf("CMD1: %s\n", *test->cmd);
			test->cmd++;
		}
		m->parser = m->parser->next;
	}
	return (0);
}

int	parse_commands(t_shell *m)
{
	t_command	*c;
	t_lexer		*l;

	l = m->lexer;
	while (l)
	{
		if (init_cmd_struct_add_to_parser_lst(&c, m) || parse_command(c, &l))
			return (ALLOC_FAILURE);
		if (parse_full_path(c, m))
			return (m->ex_status);
		if (!l)
			break ;
		while (is_token_redir(l))
		{
			if (parse_redirection(c, l->token, (l->next)->str, m))
				return (m->ex_status);
			if (l->next->next && (l->next->next)->token == WORD)
				return (p_error(UNEXPEC_TOKEN, l->str));
			if (l->next->next)
				l = l->next->next;
			else
				l = l->next;
		}
		c->cmd_splitter = l->token;
		if (l->next)
			l = l->next;
	}
	test_parser(m);
	return (OK);
}
