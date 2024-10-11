/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:30:10 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/11 18:44:00 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	token_type(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (PIPE);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (OUT);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (IN);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (HEREDOC);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (APPEND);
	else if (ft_strncmp(str, "&&", ft_strlen(str)) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
		return (OR);
	else
		return (WORD);
}

t_lexer	*get_last_token(t_lexer *lexer)
{
	while (lexer && lexer->next)
		lexer = lexer->next;
	return (lexer);
}

t_lexer	*get_first_token(t_lexer *lexer)
{
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

int	is_token_redir(t_lexer *l)
{
	if (l->token == IN || l->token == OUT || l->token == APPEND
		|| l->token == HEREDOC)
		return (1);
	return (0);
}

int	is_token_pipish(t_lexer *l)
{
	if (l->token == OR || l->token == AND || l->token == PIPE)
		return (1);
	return (0);
}
