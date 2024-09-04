/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 00:23:11 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_tokens	analyse_token(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "|", len) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "||", len) == 0)
		return (OR);
	else if (ft_strncmp(str, "&&", len) == 0)
		return (AND);
	else if (ft_strncmp(str, "<<", len) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, ">>", len) == 0)
		return (APPEND);
	else if (ft_strncmp(str, ">", len) == 0)
		return (OUT);
	else if (ft_strncmp(str, "<", len) == 0)
		return (IN);
	else if (ft_strncmp(str, "(", len) == 0)
		return (LPR);
	else if (ft_strncmp(str, ")", len) == 0)
		return (RPR);
	else if (ft_strncmp(str, "$?", len) == 0)
		return (EX_STAT);
	else if (ft_strncmp(str, "$", len) == 0)
		return (D_SIGN);
	else 
		return (COMMAND);
}

t_lexer *get_last_token(t_lexer *lexer)
{
	while (lexer->next)
		lexer = lexer->next;
	return (lexer);
}

void	*add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer *temp;

	new_token = malloc(sizeof(t_lexer));
	new_token->str = str;
	new_token->token = analyse_token(str);
	new_token->next = NULL;
    new_token->prev = NULL;
	if (*lexer == NULL)
		*lexer = new_token;
	else
	{
		temp = *lexer;
		temp = get_last_token(*lexer);
		temp->next = new_token;
		new_token->prev = temp;
	}
}

void	tokenize_non_quotes(t_lexer *lexer, char *input)
{
	char	*str;
	char	*start;
	int		length;

	while (*input)
	{
		start = input;
		input = ft_strchr(input, ' ');
		if (input)
			length = (start - input++) * -1;
		else
			length = ft_strlen(start);
		str = malloc(sizeof(char) * length + 1);
		ft_strlcpy(str, start, length + 1);
		add_to_token_list(&lexer, str);
	}
}

// void	tokenize_single_quotes(t_shell *m, char *input)
// {
// 	char	*tmp;
// 	char	*tmp_start;

// 	tmp_start = ft_strdup(input);
// 	tmp = tmp_start;
// 	while(*tmp != QUOT_MARKS)
// 		tmp++;
// 	if(*tmp == '\'')
// 	{

// 	}
	
// }

// added other WHITESPACES (eg \t)
t_lexer	*init_lexer(char *input)
{
	char	*str;
	char	*start;
	int		length;
	t_lexer	*lexer;

	lexer = NULL;
	while (input)
	{
		// if (*input == '\'')
		// 	tokenize_single_quotes(lexer, input);
		// else if (*input == '\"')
		// 	tokenize_double_quotes(lexer, input);
		// else
			tokenize_non_quotes(lexer, input);
	}
	return (lexer);
}