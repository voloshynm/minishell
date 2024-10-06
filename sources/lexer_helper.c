/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:26 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/06 19:33:16 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Pointer *s shows start of the name of variable. After moving till the end
	of UPPER letters. Upon retrieving non-UPPER, it gets the value of variable
	adds whatever left after the name and stores into tmp1. From lexer->str it
	retrieves the chars before $ sign into tmp1. Then it joins tmp2 and tmp1
	in fact replacing the name of variable with the value.
*/
static char	*replace_env_arg(char *s, t_lexer *lexer)
{
	char	*new_str;
	char	*tmp_1;
	char	*tmp_2;
	char	*start;

	start = s;
	while (*s >= 'A' && *s <= 'Z')
		s++;
	tmp_1 = ft_strndup(start, s - start);
	if (tmp_1 == NULL)
		return (NULL);
	tmp_2 = getenv(tmp_1);
	if (!tmp_2)
		tmp_2 = "";
	free(tmp_1);
	tmp_1 = ft_strjoin(tmp_2, s);
	tmp_2 = ft_strndup(lexer->str, ft_strlen(lexer->str) - ft_strlen(start)
			- 1);
	new_str = ft_strjoin(tmp_2, tmp_1);
	if (tmp_1 == NULL || tmp_2 == NULL)
		return (NULL);
	free(tmp_1);
	free(tmp_2);
	return (new_str);
}

int	process_env_arg(t_lexer *lexer)
{
	char	*s;

	s = lexer->str;
	while (*s)
	{
		if (*s == '$' && ft_isalnum(*(s + 1)))
		{
			lexer->str = replace_env_arg(++s, lexer);
			if (lexer->str == NULL)
				return (ALLOC_FAILURE);
		}
		s++;
	}
	return (OK);
}
static int	quotes_error(char *input, char opening_quote)
{
	int	count;
	int	in_quote;

	in_quote = -1;
	count = 0;
	while (*input)
	{
		if (*input == opening_quote)
		{
			count++;
			in_quote = -in_quote;
		}
		if (in_quote == -1 && (*input == '\"' || *input == '\'')
				&& *input != opening_quote)
			count++;
		input++;
	}
	return (count);
}
/*
^ Checks if quotes were properly closed, besides when its
^	single quotes inside of double quotes, or inversed.
^ Return a pointer to the closing quote of the String
*/
static char	*handle_quotes(char *input)
{
	char	quote_type;

	quote_type = *input;
	if (quotes_error(input, quote_type) % 2 == 1)
	{
		p_error(QUOTE_ERROR, "Invalid quote usage\n");
		return ("-1");
	}
	input++;
	input = ft_strchr(input, quote_type);
	while (*(input + 1) == quote_type)
		input = ft_strchr(input += 2, quote_type);
	if (*(input + 1) != 32 && *(input + 1) != 0)
		input = ft_strchr(input += 2, 32);
	return (input);
}

static char	*remove_quotes(char *str, int quotes_subtract, char quote_type)
{
	char	*new_str;
	int		in_quote;
	int		i;
	int		j;

	new_str = malloc(strlen(str - quotes_subtract) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = -1;
	while (str[i])
	{
		if (str[i] == quote_type)
			in_quote = -in_quote;
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (str[i] != quote_type && in_quote == 1)
				new_str[j++] = str[i++];
			else
				i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

static char	*process_str(char *str)
{
	char	*new_str;
	char	opening_quote_type;
	int		i;
	int		count;

	opening_quote_type = '\0';
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (opening_quote_type == '\0')
				opening_quote_type = str[i];
			count++;
		}
		i++;
	}
	if (opening_quote_type == '\0')
		return (str);
	new_str = remove_quotes(str, count, opening_quote_type);
	return (new_str);
}

char	*tokenize_input(char **input)
{
	char	*str;
	char	*start;
	int		length;

	start = *input;
	*input = ft_strpbrk(*input, " >|<&\'\"");
	if (*input)
		if (**input == '\'' || **input == '\"')
		{
			*input = handle_quotes(*input);
			if (*input && !ft_strcmp(*input, "-1"))
				return (NULL);
		}
	if (*input)
		length = (start - (*input)++) * -1;
	else
		length = ft_strlen(start);
	str = malloc(sizeof(char) * length + 1);
	if (str == NULL)
	{
		p_error(ALLOC_FAILURE, NULL);
		return (NULL);
	}
	ft_strlcpy(str, start, length + 1);
	return (process_str(str));
}

int	add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer	*temp;

	if (!*str)
		return (OK);
	new_token = malloc(sizeof(t_lexer));
	if (new_token == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
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
	return (OK);
}
