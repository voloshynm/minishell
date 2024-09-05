/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 12:57:06 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_tokens	analyse_token(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, "(", ft_strlen(str)) == 0)
		return (LPR);
	else if (ft_strncmp(str, ")", ft_strlen(str)) == 0)
		return (RPR);
	else if (ft_strncmp(str, "&&", ft_strlen(str)) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
		return (OR);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (APPEND);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (OUT);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (IN);
	else if (ft_strncmp(str, "!", ft_strlen(str)) == 0)
		return (NOT);
	else
		return (COMMAND);
}

t_lexer	*get_last_token(t_lexer *lexer)
{
	while (lexer->next)
		lexer = lexer->next;
	return (lexer);
}

void	*add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer	*temp;

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

t_lexer	*init_lexer(char *input)
{
	t_lexer *lexer;
	char *str;
	char *start;
	int length;

	lexer = NULL;
	while (input)
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
	return (lexer);
}