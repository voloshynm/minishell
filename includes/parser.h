/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:31 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/12 16:51:10 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*
**	*cmds	= linked list of t_command with all commands, separated by pipes
	**envv	= array containing keys and values for the shell environment
	ex_status	= exit status of most recently executed cmd
**	pid 	= process id for minishell instance
*/

typedef struct	s_parser
{
	t_list	*cmds;
	char	**envv;
	int		ex_status;
	pid_t	pid;
}				t_parser;

/*
**	**cmd 		= command name and parameters if any
	*full_path 	= if not builtin, path for executable, from $PATH var
	fd_in		= file descriptor to read from (defaults to stdin)
**	fd_out		= file descriptor to write to (defaults to stdout)
*/

typedef struct	s_command
{
	char	**cmd;
	char	*full_path;
	int		fd_in;
	int		fd_out;
}				t_command;

t_parser	*init_parser(t_lexer *lexer);

#endif
