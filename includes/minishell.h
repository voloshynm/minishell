/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:29:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/21 23:15:13 by mvoloshy         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h> // For open(), O_CREAT, etc.
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h> // For malloc(), free()
# include <string.h> // For strcmp(), strlen()
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h> // For read(), write(), close(), unlink()

# define PROMPT "\001\033[94m\002minishell\001\033[1;31m\002>\001\033[0m\002"
# define MAX_FDS 4096

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
	char	**envpath;
	char	*pwd;
	char	*oldpwd;
	char	*original_pwd;
	int		ex_status;
	int		pipefd[2];
	int		is_unique_cmd;
	t_token	last_splitter_token;
}			t_shell;

enum		e_err_state
{
	OK = 0,
	ALLOC_FAILURE = 1,
	UNEXPEC_TOKEN = 2,
	QUOTE_ERROR = 3,
	CMD_NOT_EXIST = 127,
	CMD_TOO_MANY_ARGS = 4,
	ENV_VAR_NOT_EXIST = 5,
	RED_IN_ERR = 6,
	RED_OUT_ERR = 7,
	RED_APPEND_ERR = 8,
	RED_HEREDOC_ERR = 9,
	TMP_FILE_CREATION_ERR = 10,
	DUP2_ERR = 11,
	CMD_TOO_FEW_ARGS = 12,
	INVAL_ENV_VAR = 13,
	PERM_DENIED = 14
};

// main.c: the main loop of minishell
void		prompt_loop(t_shell *m);
void		free_all_resources(t_shell *m);

// error_handler.c: to handle input errors and print errors
int			p_error(int err_id, void *arg);
int			p_error2(char *str, void *arg);

// parser.c: to parse tokens into commands with its path
int			parse_commands(t_shell *m, t_lexer *l);
void		free_parser(t_list **parser);

// parser_path.c: to get full path of the command for exec
int			parse_full_path(t_command *c, t_shell *m);
int			is_builtin(t_command *c);
int			is_bin(t_shell *m, t_command *p);
void		update_path_var(t_shell *m);
int			print_parser(t_shell *minihell);

// parser_redirection.c: to handle redirections
int			parse_redir(t_command *c, t_token token, char *filename,
				t_shell *m);
int			set_redir(t_command *c, t_shell *m);
void		restore_and_close_files(t_command *c, t_shell *m);

// executor.c: to execute the command
int			executor_loop(t_shell *m);
int			count_pipes(t_shell *m);
int			wait_children(t_shell *m);
int			execute_command(t_shell *m, t_list **p);
int			execute_pipe(t_shell *m, t_list **parser, int num_pipes, int i);
int			run_builtin(t_shell *m, t_list **parser, t_command *c);
int			is_inv_c_pipe(t_shell *m, t_list **p);

// signals.c: handle Ctrl-C and Ctrl-D and Ctrl-"\"
void		handle_signals(void);
void		handle_sigint(int code);
void		handle_sigquit(int code);
void		clear_rl_line(void);

// Builtins
int			echo(char **arg);
int			cd(t_shell *m, char **arg);
int			pwd(void);
int			export(t_shell *m, t_command *c);
int			unset(t_shell *m, t_command *c);
int			env(t_shell *m, t_command *c);
void		exit_shell(t_shell *m, t_command *c);

// environment.c
int			init_envp(t_shell *m, char **envp_arg);
int			add_to_envp(t_shell *m, char *key_value);
int			update_var_in_envp(t_shell *m, char *key_value);
int			rm_from_envp(t_shell *m, char *key_value);

// environment_utils2.c
void		ft_str_swap(char **a, char **b);
void		ft_str_bubble_sort(char **arr, int n);
int			sizeof_2d_array(char **arr);
int			is_var_in_envp(t_shell *m, char *key_value);

// environment_utils2.c
void		print_envp(t_shell *m);
int			is_valid_key_value(const char *key_value);
int			get_key_nmb(char **envp, char *key_value);
char		*get_key(char *key_value);
char		*get_value(char *key_value);

#endif