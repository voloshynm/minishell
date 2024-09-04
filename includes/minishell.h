/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:29:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 00:24:05 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "lexer.h"
# include "libft.h"
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

# define PROMPT "\033[94mminishell\033[1;31m>\033[0m"

typedef struct s_shell
{
	char	*input;
	t_lexer	*lexer;
}			t_shell;

void		prompt_loop(t_shell *m);
t_lexer		*init_lexer(char *input);
void		excecute(t_shell *m);
void		check_dir(t_shell *m);

#endif