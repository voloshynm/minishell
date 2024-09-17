/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:31 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/16 22:14:38 by mvoloshy         ###   ########.fr       */
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
	char	**envp;
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
	char		**cmd;
	char		*full_path;
	int			infile;
	int			outfile;
	t_token		cmd_splitter;
}				t_command;


#endif
