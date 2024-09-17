/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/17 23:02:27 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*token;

	while (lexer)
	{
		token = get_first_token(lexer);
		lexer = token->next;
		if (lexer)
			lexer->prev = NULL;
		free(token->str);
		free(token);
	}
}

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
	while (lexer->next)
		lexer = lexer->next;
	return (lexer);
}

t_lexer	*get_first_token(t_lexer *lexer)
{
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

void	add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer	*temp;

	if (!*str)
		return ;
	new_token = malloc(sizeof(t_lexer));
	if (new_token == NULL)
	{
		printf("Alloc error during tokenization");
		exit(EXIT_FAILURE);
	}
	new_token->str = str;
	new_token->token = token_type(str);
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

/*
** Checks if quotes were properly closed, besides when its
	single quotes inside of double quotes, or inversed.
** Return a pointer to the closing quote of the String
*/
char	*handle_quotes(char *input)
{
	int		count;
	char	quote_type;
	char	*last_quote;

	count = 0;
	quote_type = *input;
	last_quote = input;
	while (*input)
	{
		if (*input == quote_type)
			count++;
		input++;
	}
	if (count % 2 == 1)
	{
		printf("Invalid quote usage\n");
		exit(EXIT_FAILURE);
	}
	last_quote++;
	last_quote = ft_strchr(last_quote, quote_type);
	return (last_quote);
}

char	*tokenize_input(char **input)
{
	char	*str;
	char	*start;
	int		length;

	start = *input;
	*input = ft_strpbrk(*input, " >|<&\'\"");
	if (*input)
	{
		if (**input == '\'' || **input == '\"')
			*input = handle_quotes(*input);
	}
	if (*input)
		length = (start - (*input)++) * -1;
	else
		length = ft_strlen(start);
	str = malloc(sizeof(char) * length + 1);
	if (str == NULL)
	{
		printf("Alloc error during tokenization");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(str, start, length + 1);
	return (str);
}

void	join_same_tokens(t_lexer *lexer)
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

/*
**	Pointer *s shows start of the name of variable. After moving till the end
	of UPPER letters. Upon retrieving non-UPPER, it gets the value of variable
	adds whatever left after the name and stores into tmp1. From lexer->str it
	retrieves the chars before $ sign into tmp1. Then it joins tmp2 and tmp1
	in fact replacing the name of variable with the value.
*/

char	*replace_env_arg(char *s, t_lexer *lexer)
{
	char	*new_str;
	char	*tmp_1;
	char	*tmp_2;
	char	*start;

	start = s;
	while (*s >= 'A' && *s <= 'Z')
		s++;
	tmp_1 = ft_strndup(start, s - start);
	tmp_2 = getenv(tmp_1);
	if (!tmp_2)
	{
		printf("Environmental variable '$%s' does NOT exist\n", tmp_1);
		free(tmp_1);
		free_lexer(lexer);
		exit(EXIT_FAILURE);
	}
	free(tmp_1);
	tmp_1 = ft_strjoin(tmp_2, ++s);
	tmp_2 = ft_strndup(lexer->str, start - lexer->str);
	new_str = ft_strjoin(tmp_2, tmp_1);
	free(tmp_1);
	free(tmp_2);
	return (new_str);
}

void	process_env_arg(t_lexer *lexer)
{
	char	*s;

	if (*lexer->str == '\'' || *lexer->str == '\"')
		lexer->str = remove_first_char(lexer->str);
	s = lexer->str;
	while (*s)
	{
		if (*s == '$' && ft_isalnum(*(s + 1)))
		{
			lexer->str = replace_env_arg(++s, lexer);
			return ;
		}
		s++;
	}
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

int	unexpected_token(t_lexer *lexer)
{
	t_lexer	*start;

	start = lexer;
	if (lexer->token == PIPE || lexer->token == AND || lexer->token == OR)
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
	if ((get_last_token(lexer)->token >= 2
			&& get_last_token(lexer)->token <= 5))
		return (p_error(2, "newline"));
	if (get_last_token(lexer)->token != WORD)
		return (p_error(2, get_last_token(lexer)->str));
	return (0);
}

/*
** Goes through the input to split it by token, ft_strchr return the position
	of the found token **TOKENIZE_INPUT** split using (SPACE, >, <, |, ", ')
	(QUOTES WILL THAN HAVE A DIFFERENT TREATMENT)
** FT_STRCHR will determinate the type of TOKEN > < or | and then its
	added to the token list.
*/
int	init_lexer(t_lexer *lexer, char *input)
{
	char	*token;

	if (input_error(input))
		return (UNEXPEC_TOKEN);
	while (input)
	{
		token = tokenize_input(&input);
		add_to_token_list(&lexer, token);
		if (input)
			if (ft_strchr(">|<&", *(input - 1)))
				add_to_token_list(&lexer, ft_strndup((input - 1), 1));
	}
	analyse_tokens(lexer);
	if (unexpected_token(lexer))
		return (UNEXPEC_TOKEN);
	while (lexer)
	{
		process_env_arg(lexer);
		printf("TOKEN: %s\n", lexer->str);
		lexer = lexer->next;
	}
	return (0);
}
