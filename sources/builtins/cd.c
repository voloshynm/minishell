/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/07 21:26:48 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	upd_pwds(t_shell *m)
{
	char	new_pwd[PATH_MAX];
	char	*keyvalue_pwd;
	char	*keyvalue_oldpwd;

	free(m->oldpwd);
	m->oldpwd = m->pwd;
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (p_error2("getcwd() error", NULL));
	m->pwd = ft_strdup(new_pwd);
	keyvalue_pwd = ft_strjoin("PWD=", m->pwd);
	if (!keyvalue_pwd || update_var_in_envp(m, keyvalue_pwd))
		return (p_error(ALLOC_FAILURE, NULL));
	keyvalue_oldpwd = ft_strjoin("OLDPWD=", m->oldpwd);
	if (!keyvalue_oldpwd || update_var_in_envp(m, keyvalue_oldpwd))
		return (p_error(ALLOC_FAILURE, NULL));
	free(keyvalue_pwd);
	free(keyvalue_oldpwd);
	return (OK);
}

int	cd(t_shell *m, char **arg)
{
	char	**cmd;

	cmd = arg;
	if (cmd[2] != NULL)
		return (p_error(CMD_TOO_MANY_ARGS, NULL));
	else if (cmd[1] == NULL)
		return (p_error(CMD_TOO_FEW_ARGS, NULL));
	else if (chdir(cmd[1]) == -1)
		return (p_error2("cd", NULL));
	return (upd_pwds(m));
}
