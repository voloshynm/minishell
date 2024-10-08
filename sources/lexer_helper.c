/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:26 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/08 14:19:02 by sandre-a         ###   ########.fr       */
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
static char	*replace_env_arg(char *s, char *str)
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
	tmp_2 = ft_strndup(str, ft_strlen(str) - ft_strlen(start)
			- 1);
	new_str = ft_strjoin(tmp_2, tmp_1);
	if (tmp_1 == NULL || tmp_2 == NULL)
		return (NULL);
	free(tmp_1);
	free(tmp_2);
	return (new_str);
}

int	process_env_arg(char **str)
{
	int		s_quote;
	int		d_quote;
	char	*s;

	s_quote = 0;
	d_quote = 0;
	s = *str;
	while (*s)
	{
		if ((*s == '\'' && !d_quote) || (*s == '\"' && !s_quote))
		{
			s_quote ^= (*s == '\'');
			d_quote ^= (*s == '\"');
			s++;
			continue ;
		}
		if (!s_quote && *s == '$' && ft_isalnum(*(s + 1)))
		{
			*str = replace_env_arg(++s, *str);
			if (*str == NULL)
				return (ALLOC_FAILURE);
		}
		s++;
	}
	return (OK);
}

int	quotes_error(char *input)
{
	int	s_quote;
	int	d_quote;
	int	i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !d_quote)
			s_quote ^= 1;
		else if (input[i] == '\"' && !s_quote)
			d_quote ^= 1; 
		i++;
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
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
	while (*(input + 1) == quote_type)
		input = ft_strchr(input += 2, quote_type);
	if (*(input + 1) != 32 && *(input + 1) != 0)
		input = ft_strchr(input += 2, 32);
	return (input);
}

static char	*remove_quotes(char *str, char quote_type, int in_quote)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
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
	if (ft_strchr(str, '$'))
		process_env_arg(&str);
	if (opening_quote_type == '\0')
		return (str);
	new_str = remove_quotes(str, opening_quote_type, -1);
	free(str);
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
			*input = handle_quotes(*input);
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
		temp = get_last_token(*lexer);
		temp->next = new_token;
		new_token->prev = temp;
	}
	return (OK);
}
