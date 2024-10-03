/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/03 19:00:36 by mvoloshy         ###   ########.fr       */
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
	*cur_cmd = NULL;
	return (0);
}

int	parse_commands(t_shell *m, t_lexer *l)
{
	t_command	*c;
	
	while (l)
	{
		if (init_cmd_struct_add_to_parser_lst(&c, m) || parse_command(c, &l))
			return (ALLOC_FAILURE);
		parse_full_path(c, m);
		while (l && is_token_redir(l))
		{
			if (parse_redirection(c, l->token, (l->next)->str, m))
				return (m->ex_status);
			if (g_sig_pid == 1)
				return (RED_HEREDOC_ERR);
			if (l->next->next && (l->next->next)->token == WORD)
				return (p_error(UNEXPEC_TOKEN, l->str));
			l = l->next->next;
		}
		if (l && is_token_pipish(l))
		{
			c->cmd_splitter = l->token;
			m->last_splitter_token = l->token;
			l = l->next;
		}
	}
	return (OK);
}

void	free_parser(t_list **parser)
{
	t_list		*p;
	t_command	*command;
	int			i;

	if (parser == NULL)
		return;
	while (*parser)
	{
		p = *parser;
		*parser = (*parser)->next;
		command = ((t_command *)p->content);
		if (command->cmd)
		{
			i = 0;
			while (command->cmd[i])
			{
				free(command->cmd[i]);
				i++;
			}
			free(command->cmd);
		}
		free(command->full_path);
		free(command);
		free(p);
	}
	*parser = NULL;
}
