/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:29:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/29 15:41:35 by mvoloshy         ###   ########.fr       */
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
# include <errno.h>
# include <stdlib.h> // For malloc(), free()
# include <string.h> // For strcmp(), strlen()
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h> // For read(), write(), close(), unlink()
# include <sys/ioctl.h>


# define PROMPT "\033[94mminishell\033[1;31m>\033[0m"
# define MAX_FDS 4096

extern int	g_sig_pid;

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
	int		exit_statuses[MAX_FDS];
	int		pipefd[2];
	t_token	last_splitter_token;
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
	DUP2_ERR = 11,
};

// main.c: the main loop of minishell
void	prompt_loop(t_shell *m);

// error_handler.c: to handle input errors and print errors
int		p_error(int err_id, void *arg);
int		p_error2(char *str, void *arg);
int		input_error(char *input);

// parser.c: to parse tokens into commands with its path
int		parse_commands(t_shell *m, t_lexer *l);
void	free_parser(t_list **parser);

// parser_path.c: to get full path of the command for exec
int		parse_full_path(t_command *c, t_shell *m);
int		is_builtin(t_command *p);
int		is_bin(t_shell *m, t_command *p);

int		print_parser(t_shell *minihell);

// parser_redirection.c: to handle redirections
int		parse_redirection(t_command *c, t_token token, char *filename,
			t_shell *m);
int		setup_redirection(t_command *c, t_shell *m);
void	restore_and_close_files(t_command *c, t_shell *m);

// executor.c: to execute the command
int		executor_loop(t_shell *m);
int		count_pipes(t_shell *m);
int		wait_children(t_shell *m);
int		execute_command(t_shell *m, t_list **p);
int		execute_pipe(t_shell *m, t_list **parser, int num_pipes, int i);


// signals.c: handle Ctrl-C and Ctrl-D and Ctrl-"\"
void	handle_signals(void);

void handle_sigint(int code);
#endif