/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/01 22:54:15 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	upd_pwds(char oldpwd[PATH_MAX], t_shell *m)
{
	char	pwd[PATH_MAX];
	
	m->oldpwd = oldpwd;
	if (!getcwd(pwd, sizeof(pwd)))
		return(p_error2("getcwd() error", NULL));
	m->pwd = pwd;
	return (OK);
}

int		cd(char **arg, t_shell *m)
{
	char	**cmd;
	char	oldpwd[PATH_MAX];
	
	cmd = arg;
	if (cmd[2] != NULL)
		return(p_error(CMD_TOO_MANY_ARGS, NULL));
	else if (!getcwd(oldpwd, sizeof(oldpwd)))
		return(p_error2("getcwd() error", NULL));
	else if (cmd[1] == NULL)
		return(p_error(CMD_TOO_FEW_ARGS, NULL));
	else if (chdir(cmd[1]) == -1)
		return(p_error2("cd", NULL));
	return(upd_pwds(oldpwd, m));
}
