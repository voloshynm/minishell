#include "../includes/minishell.h"

int	export(t_shell *m, t_command *c)
{
	int		i;
	int		is_valid;

	i = 1;
	if (c->cmd[i] == NULL || c->cmd[i][0] == '\0')
		print_envp(m);
	while (c->cmd[i] != NULL)
	{
		is_valid = is_valid_key_value(c->cmd[i]);
		if (!is_valid)
			return (p_error(INVAL_ENV_VAR, c->cmd[i]));
		if (is_var_in_envp(m, c->cmd[i]))
			update_var_in_envp(m, c->cmd[i]);
		else
			add_to_envp(m, c->cmd[i]);
		i++;
	}
	return (0);
}