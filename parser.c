// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
// /*   Updated: 2024/09/17 16:58:18 by mvoloshy         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "includes/parser.h"

// int	is_token_redir(t_lexer *l)
// {
// 	if (l->token != IN || l->token != OUT
// 			|| l->token != APPEND || l->token != HEREDOC)
// 		return (1);
// 	return (0);
// }

// int	is_cmd_start_err(t_lexer *l)
// {
// 	int	err;

// 	err = 0;
// 	if (l->token != WORD || is_token_redir(l->token))
// 		printf("syntax error near unexpected token `%s'\n", l->token);
// 		err = p_error(UNEXPEC_TOKEN, &l->token);
// 		free_lexer();
// 		free_parser();
// 		return (err);
// }

// // void	is_cmd_start_err(t_lexer *l)
// // {
// // 	if (l->token != WORD || l->token != IN || l->token != OUT
// // 				|| l->token != APPEND || l->token != HEREDOC)
// // 		printf("syntax error near unexpected token `%s'\n", l->token);
// // 		free_lexer();
// // 		free_parser();
// // 		exit(EXIT_FAILURE);
// // }

// int	parse_commands(t_parser **p, t_lexer **l)
// {
// 	t_list		*cmds_lst_el;
// 	t_command	*c;
// 	t_command	*cur_cmd;

// 	while ((*l)->token)
// 	{
// 		if (is_cmd_start_err((*l)->token))
// 			return (UNEXPEC_TOKEN);		// check that we have a proper input, specifically first token
// 		c = ft_calloc(1, sizeof(t_command));
// 		cmds_lst_el = ft_lstnew(c);
// 		ft_lstadd_back(&(*p)->cmds, cmds_lst_el);	// create a list element c of a struct t_command and add it to t_list cmds
// 		if (!c || !cmds_lst_el || !(*p)->cmds)
// 			return (ALLOC_FAILURE);
// //		parse_full_path(c, (*l)->token);		// define the actual command, based on the fist token and then check if it is a builtin. Consequently assign a path of the command
// 		cur_cmd = c->cmd;						// ensure we don't lose the initial pointer during iteration and use a temp one instead
// 		while ((*l)->token == WORD)
// 		{
// 			cur_cmd = (*l)->token;
// 			*l = (*l)->next;
// 			cur_cmd++;
// 		}
// 		while (is_token_redir((*l)->token))
// 			parse_redirection(&c, (*l)->token);		// process the type of redirection and thus record into infile & outfile
// 		c->cmd_splitter = (*l)->token;
// 	}
// }

// t_parser	*init_parser(t_lexer **lexer, t_shell **m)
// {
// 	t_parser	*p;

// 	parse_commands(&p, lexer);
// 	parse_remaining_parser(&p, m);
// }

