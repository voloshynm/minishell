/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/30 22:54:01 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	unexpected_token(t_lexer *lexer)
{
	t_lexer	*start;

	start = lexer;
	if (lexer && (lexer->token == PIPE || lexer->token == AND
			|| lexer->token == OR))
		return (p_error(2, lexer->str));
	while (start)
	{
		if (!start->next)
			break ;
		if (is_token_redir(start) && is_token_redir(start->next))
			return (p_error(2, start->next->str));
		if (is_token_pipish(start) && is_token_pipish(start->next))
			return (p_error(2, start->next->str));
		start = start->next;
	}
	if (lexer && (get_last_token(lexer)->token >= 2
			&& get_last_token(lexer)->token <= 5))
		return (p_error(2, "newline"));
	if (lexer && get_last_token(lexer)->token != WORD)
		return (p_error(2, get_last_token(lexer)->str));
	return (0);
}

static void	join_same_tokens(t_lexer *lexer)
{
	if (lexer->next->token == IN)
		lexer->str = ft_strdup("<<");
	else if (lexer->next->token == OUT)
		lexer->str = ft_strdup(">>");
	else if (lexer->next->token == PIPE)
		lexer->str = ft_strdup("||");
	else
		lexer->str = ft_strdup("&&");
}

static char	get_quote_type(char *token)
{
	char	opening_quote_type;

	if (ft_strpbrk(token, "\'\""))
		opening_quote_type = *(ft_strpbrk(token, "\'\""));
	else
		opening_quote_type = ' ';
	return (opening_quote_type);
}

/*
^ Goes through the input to split it by token, ft_strchr return the position
^	of the found token **TOKENIZE_INPUT** split using (SPACE, >, <, |, ", ')
^	(QUOTES WILL THAN HAVE A DIFFERENT TREATMENT)
^ FT_STRCHR will determinate the type of TOKEN > < or | and then its
^	added to the token list.
TODO: implement error handler for "add_to_token_list(lexer, token);""
*/
int	init_lexer(t_lexer **lexer, char *input)
{
	char	*token;
	char	q_type;

	if (quotes_error(input))
	{
		p_error(QUOTE_ERROR, "Invalid quote usage\n");
		return (-1);
	}
	while (input)
	{
		token = tokenize_input(&input);
		q_type = get_quote_type(token);
		token = process_str(token, q_type);
		if (!token)
			continue ;
		add_to_token_list(lexer, token, q_type);
		if (input)
			if (ft_strchr(">|<&", *(input - 1)))
				add_to_token_list(lexer, ft_strndup((input - 1), 1), q_type);
	}
	analyse_tokens(*lexer);
	if (unexpected_token(*lexer))
		return (UNEXPEC_TOKEN);
	return (0);
}

void	analyse_tokens(t_lexer *lexer)
{
	t_lexer	*temp;

	temp = lexer;
	while (lexer)
	{
		if (!lexer->next)
			break ;
		if ((lexer->token == IN && lexer->next->token == IN)
			|| (lexer->token == OUT && lexer->next->token == OUT)
			|| (lexer->token == PIPE && lexer->next->token == PIPE)
			|| (lexer->str[0] == '&' && lexer->next->str[0] == '&'))
		{
			free(lexer->str);
			join_same_tokens(lexer);
			temp = lexer->next->next;
			free(lexer->next->str);
			free(lexer->next);
			lexer->next = temp;
			lexer->token = token_type(lexer->str);
			if (temp)
				temp->prev = lexer;
		}
		lexer = lexer->next;
	}
}
