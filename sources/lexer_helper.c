/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:26 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/24 15:29:51 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*process_str(char *str, char ***envp)
{
	char	*new_str;
	char	opening_quote_type;
	int		i;
	int		count;

	if (ft_strpbrk(str, "\'\""))
		opening_quote_type = *(ft_strpbrk(str, "\'\""));
	else
		opening_quote_type = '\0';
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == opening_quote_type)
			count++;
	}
	if (ft_strchr(str, '$'))
		process_env_arg(&str, envp);
	new_str = remove_quotes(str, opening_quote_type, -1);
	free(str);
	return (new_str);
}

static int	get_length(char *start, char **input)
{
	int	length;
	int	i;

	i = 0;
	if (*input)
		length = (start - (*input)++) * -1;
	else
		length = ft_strlen(start);
	while (i <= length)
	{
		if ((start[i] == '\"' && start[i + 1] == '\"') || (start[i] == '\''
				&& start[i + 1] == '\''))
		{
			length++;
			break ;
		}
		i++;
	}
	return (length);
}

char	*tokenize_input(char **input, char ***envp)
{
	char	*str;
	char	*start;
	int		length;

	start = *input;
	*input = ft_strpbrk(*input, " >|<&\'\"");
	if (*input)
		if (**input == '\'' || **input == '\"')
			*input = handle_quotes(*input);
	length = get_length(start, input);
	if (!length)
		return ("");
	str = malloc(sizeof(char) * length + 1);
	if (str == NULL)
		return (p_error(ALLOC_FAILURE, NULL), NULL);
	ft_strlcpy(str, start, length + 1);
	return (process_str(str, envp));
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
