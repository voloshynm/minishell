/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:29:37 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/31 00:02:14 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export(t_shell *m, t_command *c, char **v, int i)
{
	int		is_valid;

	if (c->cmd[i] == NULL || c->cmd[i][0] == '\0')
	{
		v = ft_str_bubble_sort(m->envp, sizeof_2d_array(m->envp));
		i = -1;
		while (v[++i] && *(v[i]))
			printf("%s\n", v[i]);
		free_sorted_array(v);
	}
	while (c->cmd[i] != NULL)
	{
		is_valid = is_valid_key_value(c->cmd[i]);
		if (!is_valid)
		{
			p_error(INVAL_ENV_VAR, c->cmd[i]);
			return (1);
		}
		if (is_var_in_envp(m, c->cmd[i]))
			update_var_in_envp(m, c->cmd[i]);
		else
			add_to_envp(m, c->cmd[i]);
		i++;
	}
	return (0);
}
