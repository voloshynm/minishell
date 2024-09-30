/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/30 22:53:02 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(t_command *c)
{
	if (c->cmd[2] != NULL && c->cmd[2][0] != '\0')
		return(p_error(CMD_TOO_MANY_ARGS, NULL));
	if (c->cmd[1] == NULL)
		return(p_error2("cd", NULL));
	if (chdir(c->cmd[1]) == -1)
		return(p_error2("cd", NULL));
	return (OK);
}