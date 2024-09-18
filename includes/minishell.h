/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:29:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/18 22:19:51 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include <stdio.h>
# include <dirent.h>
# include <fcntl.h> // For open(), O_CREAT, etc.
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h> // For malloc(), free()
# include <string.h> // For strcmp(), strlen()
# include <termios.h>
# include <unistd.h> // For read(), write(), close(), unlink()

# define PROMPT "\033[94mminishell\033[1;31m>\033[0m"

/*
**	*cmds	= linked list of t_command with all commands, separated by pipes
	**envv	= array containing keys and values for the shell environment
	ex_status	= exit status of most recently executed cmd
**	pid 	= process id for minishell instance
*/

typedef struct s_shell
{
	char	*input;
	t_lexer	*lexer;
	t_list	*parser;
	pid_t	pid;
	char	**envp;
	char	*pwd;
	char	*oldpwd;
	int		ex_status;
}			t_shell;

enum		e_err_state
{
	OK = 0,
	ALLOC_FAILURE = 1,
	UNEXPEC_TOKEN = 2,
	QUOTE_ERROR = 3,
	CMD_NOT_EXIST = 4,
	ENV_VAR_NOT_EXIST = 5,
	RED_IN_ERR = 6,
	RED_OUT_ERR = 7,
	RED_APPEND_ERR = 8,
	RED_HEREDOC_ERR = 9,
	TMP_FILE_CREATION_ERR = 10,
	DUP2_ERR = 11
};

void		prompt_loop(t_shell *m);

int			p_error(int err_id, void *arg);
int			input_error(char *input);

//int			excecute(t_exec *exec);
int			command_exists(t_shell *m);

#endif