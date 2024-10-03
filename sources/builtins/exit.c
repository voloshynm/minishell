#include "../../includes/minishell.h"

void	exit_shell(t_shell *m)
{
    free_all_resources(m);
    printf("exit\n");
	exit(0);
}