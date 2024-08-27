#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "color.h"

#define PROMPT "\033[94mminishell\033[1;31m>\033[0m" " "

typedef struct shell_s
{
	char	*input;
}			shell_t;


void prompt_loop(shell_t *m);

#endif 