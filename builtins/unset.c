#include "../includes/minishell.h"

int	unset(t_shell *m, t_command *c)
{
	int		i;

	i = 1;
	while (c->cmd[i] != NULL)
	{
		if (rm_from_envp(m, c->cmd[i]))
			return (ALLOC_FAILURE);
		i++;
	}
	return (0);
}