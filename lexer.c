/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/12 00:17:32 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

t_tokens	token_type(char *str)
{
	if (str[0] == '\'')
		return (S_QUOTE);
	if (str[0] == '\"')
		return (D_QUOTE);
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (PIPE);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (REDIR_APPEND);
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

char	*ft_strpbrk(const char *s, const char *c)
{
	const char	*str = s;
	int			i;

	while (*str)
	{
		i = 0;
		while (c[i])
		{
			if (*str == c[i])
				return ((char *)str);
			i++;
		}
		str++;
	}
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*t_s;
	char	*new_str;
	char	*start;

	t_s = (char *)s;
	i = 0;
	new_str = malloc((n + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*t_s && i < n)
	{
		*new_str = *t_s;
		new_str++;
		t_s++;
		i++;
	}
	*new_str = 0;
	return (start);
}

int	count_quotes(char *input, char quote_type)
{
	int	count;

	count = 0;
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
	return (count);
}

char	*handle_quotes(char *input)
{
	int		count;
	char	quote_type;

	quote_type = *input;
	count = count_quotes(input, quote_type);
	input++;
	input = ft_strchr(input, quote_type);
	return (input);
}

char	*tokenize_input(char **input)
{
	char	*str;
	char	*start;
	int		length;

	start = *input;
	*input = ft_strpbrk(*input, " >|<\'\"");
	if (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			*input = handle_quotes(*input);
		}
	}
	if (*input)
		length = (start - (*input)++) * -1;
	else
		length = ft_strlen(start);
	str = malloc(sizeof(char) * length + 1);
	ft_strlcpy(str, start, length + 1);
	return (str);
}

void	analyse_tokens(t_lexer **lexer)
{
	t_lexer	*temp;

	temp = *lexer;
	while ((*lexer)->next)
	{
		if (((*lexer)->token == REDIR_IN && (*lexer)->next->token == REDIR_IN)
			|| ((*lexer)->token == REDIR_OUT
				&& (*lexer)->next->token == REDIR_OUT))
		{
			free((*lexer)->str);
			if ((*lexer)->next->token == REDIR_IN)
				(*lexer)->str = ft_strdup("<<");
			else
				(*lexer)->str = ft_strdup(">>");
			temp = (*lexer)->next->next;
			free((*lexer)->next->str);
			free((*lexer)->next);
			(*lexer)->next = temp;
			(*lexer)->token = token_type((*lexer)->str);
			temp->prev = *lexer;
			return ;
		}
		*lexer = (*lexer)->next;
	}
}

void	remove_first_char(t_lexer *lexer)
{
	char	*old_str;
	char	*new_str;

	old_str = lexer->str;
	new_str = ft_strdup(++old_str);
	free(lexer->str);
	lexer->str = new_str;
}

char	*replace_env_arg(char *s, t_lexer *lexer)
{
	char	*new_str;
	char	*tmp_1;
	char	*tmp_2;
	char	*start;

	start = s;
	while (ft_isalnum(*s))
//	while (*s > 65 && *s < 90)
//	somehow I cannot check for only UPPERCASE, wtf. the pointer doesnt move thus the segfault fir getenv
	{
//		printf("DBG: *s %c\n", *s);
		s++;
	}
	tmp_1 = ft_strndup(start, s - start);
//	printf("DBG: s - 1 %s\n", s - 1);
//	printf("DBG: tmp_1 %s\n", tmp_1);
	tmp_2 = getenv(tmp_1);
//	printf("DBG: tmp_2 %s\n", tmp_2);
	if (!tmp_2)
	{
		printf("Environmental variable '$%s' does NOT exist\n", tmp_1);
		free(tmp_1);
		exit(0);
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
	char	c;
	char	*s;
	
	c = *lexer->str;
	if (c == '\'' || c == '\"')
	{
		remove_first_char(lexer);
		if (c == '\'')
			return ;
	}
	s = lexer->str;
	while (*s)
	{
		if (*s == '$' && ft_isalnum(*(s + 1)))
		{
			lexer->str = replace_env_arg(++s, lexer);
			return;
		}
		s++;
	}
}

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;
	char	*token;

	lexer = NULL;
	while (input)
	{
		token = tokenize_input(&input);
		add_to_token_list(&lexer, token);
		if (input)
			if (ft_strchr(">|<", *(input - 1)))
				add_to_token_list(&lexer, ft_strndup((input - 1), 1));
	}
	analyse_tokens(&lexer);
	lexer = get_first_token(lexer);
	t_lexer	*tmp = lexer;
	while (tmp)
	{
		process_env_arg(tmp);
		printf("TOKEN: %s\n", tmp->str);
		tmp = tmp->next;
	}
	return (lexer);
}
