/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:29:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/16 21:10:00 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "lexer.h"
# include "parser.h"
# include "libft.h"
# include "executor.h"
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>

# define PROMPT "\033[94mminishell\033[1;31m>\033[0m"

typedef struct s_shell
{
	char		*input;
	t_lexer		*lexer;
	t_parser	*parser;
	t_exec		exec;
}			t_shell;

void		prompt_loop(t_shell *m);

#endif