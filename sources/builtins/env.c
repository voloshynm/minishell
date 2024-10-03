#include "../../includes/minishell.h"

int	env(t_shell *m, t_command *c)
{
	if (c->cmd[1] != NULL)
		return(p_error(CMD_TOO_MANY_ARGS, NULL));
	print_envp(m);
	return (0);
}