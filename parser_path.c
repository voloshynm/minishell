/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:08:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/19 22:03:21 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_builtin(t_shell *m)
{
	DIR				*directory;
	struct dirent	*entry;
	char			path[PATH_MAX];
	t_command		*p;

	p = ((t_command *)(m->parser->content));
	getcwd(path, sizeof(path));
	p->full_path = ft_strjoin(path, "/builtins");
	directory = opendir(p->full_path);
	while (directory)
	{
		entry = readdir(directory);
		if (!entry)
			break ;
		if (!ft_strncmp(p->cmd[0], entry->d_name, ft_strlen(p->cmd[0])))
		{
			closedir(directory);
			return (1);
		}
	}
	free(p->full_path);
	p->full_path = NULL;
	closedir(directory);
	return (0);
}

int		is_bin(t_shell *m)
{
	DIR *directory;
	struct dirent *entry;
	int i;
	t_command *p;

	p = ((t_command *)(m->parser->content));
	i = 0;
	while (m->envp[i])
	{
		directory = opendir(m->envp[i]);
		while (directory)
		{
			entry = readdir(directory);
			if (!entry)
				break ;
			if (!ft_strncmp(p->cmd[0], entry->d_name, ft_strlen(p->cmd[0])))
			{
				p->full_path = m->envp[i];
				closedir(directory);
				return (1);
			}
		}
		closedir(directory);
		i++;
	}
	return (0);
}