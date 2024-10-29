/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/29 17:14:43 by mvoloshy         ###   ########.fr       */
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

static int	parse_command(t_command *c, t_lexer **l, t_shell *m)
{
	char	**cur_cmd;
	char	**cur_q_type;

	cur_cmd = ft_calloc(get_cmd_len(*l) + 1, sizeof(char *));
	cur_q_type = ft_calloc(get_cmd_len(*l) + 1, sizeof(char *));
	if (!cur_cmd || !cur_q_type)
		return (p_error(ALLOC_FAILURE, NULL));
	c->cmd = cur_cmd;
	c->q_type = cur_q_type;
	while (*l && (*l)->token == WORD)
	{
		*cur_cmd = ft_strdup((*l)->str);
		*cur_q_type = ft_strdup(&((*l)->q_type));
		if (!*cur_cmd || !*cur_q_type)
			return (p_error(ALLOC_FAILURE, NULL));
		*l = (*l)->next;
		cur_cmd++;
		cur_q_type++;
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
		c->q_type[i] = ft_strdup(&((*l)->q_type));
		if (!c->cmd[i] || !c->q_type[i])
			return (p_error(ALLOC_FAILURE, NULL));
		*l = (*l)->next;
		i++;
	}
	c->cmd[i] = 0;
	c->q_type[i] = 0;
	return (0);
}

static void	parse_redir_loop(t_shell *m, t_lexer **l, t_command *c)
{
	if (!m->ex_status && (*l)->prev && (*l)->prev->prev
		&& is_token_redir((*l)->prev->prev))
	{
		if (c->infile && ((*l)->token == IN || (*l)->token == HEREDOC))
			close(c->infile);
	}
	if (!m->ex_status)
		m->ex_status = parse_redir(c, (*l)->token, (*l)->next, m);
	(*l) = (*l)->next->next;
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
				parse_redir_loop(m, &l, c);
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
