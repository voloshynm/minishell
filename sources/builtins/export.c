/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:37 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/04 15:32:34 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export(t_shell *m, t_command *c)
{
	int	i;
	int	is_valid;

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
