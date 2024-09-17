/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/16 22:15:45 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

void	check_command_start(t_lexer *l)
{
	if (l->token != WORD || l->token != IN || l->token != OUT
				|| l->token != APPEND || l->token != HEREDOC)
		printf("syntax error near unexpected token `%s'\n", l->token);
		free_lexer();
		free_parser();
		exit(EXIT_FAILURE);
}

void	parse_commands(t_parser **p, t_lexer **l)
{
	t_list		*cmds;
	t_command	*c;
	t_command	**cur_cmd;

	while ((*l)->token)
	{
		check_command_start((*l)->token);		// check that we have a proper input, specifically first token
		ft_lstadd_back(&cmds, ft_lstnew(c));	// create a list element c of a struct t_command and add it to t_list cmds
		parse_full_path(c, (*l)->token);		// define the actual command, based on the fist token and then check if it is a builtin. Consequently assign a path of the command
		cur_cmd = c->cmd;						// ensure we don't lose the initial pointer during iteration and use a temp one instead
		while ((*l)->token == WORD)
		{
			cur_cmd = (*l)->token;
			*l = (*l)->next;
			cur_cmd++;
		}
		while ((*l)->token == IN || (*l)->token == OUT
				|| (*l)->token == APPEND || (*l)->token == HEREDOC)
			parse_redirection(&c, (*l)->token);		// process the type of redirection and thus record into infile & outfile
		c->cmd_splitter = (*l)->token;
	}
}

t_parser	*init_parser(t_lexer **lexer, t_shell **m)
{
	t_parser	*p;

	parse_commands(&p, lexer);
	parse_remaining_parser(&p, m);
}

