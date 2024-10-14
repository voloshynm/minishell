/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:23:35 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/10 19:35:26 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
**	WORD,        	Represents commands and arguments (grep, cat, echo)
**	PIPE,         	Represents the pipe operator (|)
**	REDIR_IN,		Represents input redirection (<)
**	REDIR_OUT,		Represents output redirection (>)
**	REDIR_APPEND,	Represents append redirection (>>)
**	REDIR_HEREDOC,	Represents heredoc redirection (<<)
*/
typedef enum e_token
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	AND,
	OR,
	S_QUOTE,
	D_QUOTE,
	NONE
}					t_token;

/*
**	lexer stores tokenized elements of the input.
**	during the tokenization it consumes > and > and then conbines into e.g.>>
**	tokenizer checks for the erroneous input, after tokenization and analysis
**	eventually we replace the env variable with its value
**
**	t_token	token stores the type of the token
**	char *str stores the string value of the token
** 	*next and *prev are links to the following elements of the list of tokens
*/
typedef struct s_lexer
{
	char			*str;
	t_token			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

// lexer_utils.c
t_lexer		*get_last_token(t_lexer *lexer);
t_lexer		*get_first_token(t_lexer *lexer);
t_token		token_type(char *str);
int			is_token_redir(t_lexer *l);
int			is_token_pipish(t_lexer *l);

// lexer_helper.c
int			add_to_token_list(t_lexer **lexer, char *str);
char		*tokenize_input(char **input);
int			process_env_arg(char **str);
char		*process_str(char *str);

// lexer_quotes.c
int			quotes_error(char *input);
char		*handle_quotes(char *input);
char		*remove_quotes(char *str, char quote_type, int in_quote);

// lexer.c
int			init_lexer(t_lexer **lexer, char *input);
void		analyse_tokens(t_lexer *lexer);
void		free_lexer(t_lexer **lexer);

#endif