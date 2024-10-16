/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/16 02:56:45 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	create a list element c of a struct t_command and add it to t_list cmds
*/
static int	init_cmd_struct_add_to_parser_lst(t_command **c, t_shell *m)
{
	t_list	*cmds_lst_el;

	*c = ft_calloc(1, sizeof(t_command));
	if (!(*c))
		return (p_error(ALLOC_FAILURE, NULL));
	cmds_lst_el = ft_lstnew(*c);
	ft_lstadd_back(&m->parser, cmds_lst_el);
	if (!cmds_lst_el || !m->parser)
	{
		free(*c);
		return (p_error(ALLOC_FAILURE, NULL));
	}
	(*c)->infile = STDIN_FILENO;
	(*c)->outfile = STDOUT_FILENO;
	(*c)->cmd_splitter = NONE;
	(*c)->last_splitter_token = m->last_splitter_token;
	return (OK);
}

static int	get_cmd_len(t_lexer *lexer)
{
	int		len;
	int		redir;
	t_lexer	*l;

	l = lexer;
	len = 0;
	redir = 0;
	while (l && !is_token_pipish(l))
	{
		if (is_token_redir(l))
			redir += 2;
		len++;
		l = l->next;
	}
	return (len);
}

static int	parse_command(t_command *c, t_lexer **l, t_shell *m)
{
	char	**cur_cmd;

	cur_cmd = ft_calloc(get_cmd_len(*l) + 1, sizeof(char *));
	if (!cur_cmd)
		return (p_error(ALLOC_FAILURE, NULL));
	c->cmd = cur_cmd;
	while (*l && (*l)->token == WORD)
	{
		*cur_cmd = ft_strdup((*l)->str);
		if (!*cur_cmd)
			return (p_error(ALLOC_FAILURE, NULL));
		*l = (*l)->next;
		cur_cmd++;
	}
	parse_full_path(c, m);
	*cur_cmd = NULL;
	return (0);
}

static int	add_to_command_list(t_command *c, t_lexer **l)
{
	int	i;

	i = 0;
	while (c->cmd[i])
		i++;
	while (*l && (*l)->token == WORD)
	{
		c->cmd[i] = ft_strdup((*l)->str);
		if (!c->cmd[i])
			return (p_error(ALLOC_FAILURE, NULL));
		*l = (*l)->next;
		i++;
	}
	c->cmd[i] = 0;
	return (0);
}

int	parse_commands(t_shell *m, t_lexer *l)
{
	t_command	*c;

	while (l)
	{
		m->ex_status = 0;
		if (init_cmd_struct_add_to_parser_lst(&c, m) || parse_command(c, &l, m))
			return (ALLOC_FAILURE);
		while (l && !is_token_pipish(l))
		{
			if (is_token_redir(l))
			{
				if (!m->ex_status)
					m->ex_status = parse_redir(c, l->token, (l->next)->str, m);
				l = l->next->next;
			}
			add_to_command_list(c, &l);
		}
		if (l && is_token_pipish(l))
		{
			c->cmd_splitter = l->token;
			m->last_splitter_token = l->token;
			l = l->next;
		}
	}
	return (m->ex_status);
}
