/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:29:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/17 17:27:44 by mvoloshy         ###   ########.fr       */
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
	t_exec		*exec;
	pid_t		pid;
	int			ex_status;
}			t_shell;

enum e_err_state
{
	OK = 0,
	ALLOC_FAILURE = 1,
	UNEXPEC_TOKEN = 2,
	QUOTE_ERROR = 3,
	CMD_NOT_EXIST = 4,
	ENV_VAR_NOT_EXIST = 5,
};

void		prompt_loop(t_shell *m);

int	p_error(int err_id, void **arg_1);

#endif