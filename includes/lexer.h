/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:23:35 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/17 21:17:49 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

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
	OR
}					t_token;

/*
**	explain this struct, especially Im curious wtf is i? :) - SERGIO
**	
*/
typedef struct s_lexer
{
	char			*str;
	t_token			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

t_lexer				*get_last_token(t_lexer *lexer);
t_lexer				*get_first_token(t_lexer *lexer);

int					init_lexer(t_lexer *lexer, char *input);

#endif