#include "../includes/minishell.h"

int	export(t_shell *m, t_command *c)
{
	int		i;

	i = 1;
	if (c->cmd[i] == NULL || c->cmd[i][0] == '\0')
		print_envp(m);
	while (c->cmd[i] != NULL)
	{
		if (add_to_envp(m, c->cmd[i]))
			return (-1);
		i++;
	}
	return (0);
}