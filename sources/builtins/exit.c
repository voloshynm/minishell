#include "../../includes/minishell.h"

void	exit(t_shell *m)
{
    free_all_resources(m);
    printf("exit\n");
	exit(0);
}