/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:51:16 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/16 03:03:34 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
char	*handle_quotes(char *input)
{
	char	*temp;
	int		quote_count;
	char	quote_type;

	quote_count = 0;
	quote_type = *input;
	while (*input && *input != 32)
	{
		if (*input == quote_type)
			quote_count++;
		input++;
	}
	if (quote_count % 2 == 0)
	{
		return (input - 1);
	}
	temp = ft_strchr(input, quote_type);
	if (*(temp + 1) == 32)
		return (ft_strchr(input, quote_type));
	return (NULL);
}

char	*remove_quotes(char *str, char quote_type, int in_quote)
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
	new_str[j] = 0;
	return (new_str);
}
