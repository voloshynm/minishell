/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:26 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/20 15:15:18 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	tmp_2 = getenv(tmp_1);
	if (!tmp_2)
		tmp_2 = "";
	free(tmp_1);
	tmp_1 = ft_strjoin(tmp_2, s);
	tmp_2 = ft_strndup(lexer->str,
			ft_strlen(lexer->str) - ft_strlen(start) - 1);
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
			lexer->str = replace_env_arg(++s, lexer);
		s++;
	}
}

/*
** Checks if quotes were properly closed, besides when its
	single quotes inside of double quotes, or inversed.
** Return a pointer to the closing quote of the String
*/
static char	*handle_quotes(char *input)
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
