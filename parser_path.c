/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:08:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/20 23:14:54 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_builtin(t_command *c)
{
	DIR				*directory;
	struct dirent	*entry;
	char			path[PATH_MAX];

	getcwd(path, sizeof(path));
	c->full_path = ft_strjoin(path, "/builtins");
	directory = opendir(c->full_path);
	while (directory)
	{
		entry = readdir(directory);
		if (!entry)
			break ;
		if (!ft_strncmp(c->cmd[0], entry->d_name, ft_strlen(c->cmd[0])))
		{
			closedir(directory);
			return (1);
		}
	}
	free(c->full_path);
	c->full_path = NULL;
	closedir(directory);
	return (0);
}

int	is_bin(t_shell *m, t_command *c)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	i = -1;
	while (m->envp[++i])
	{
		directory = opendir(m->envp[i]);
		while (directory)
		{
			entry = readdir(directory);
			if (!entry)
				break ;
			if (!ft_strncmp(c->cmd[0], entry->d_name, ft_strlen(c->cmd[0])))
			{
				c->full_path = m->envp[i];
				closedir(directory);
				return (1);
			}
		}
		closedir(directory);
	}
	return (0);
}

int	parse_full_path(t_command *c, t_shell *m)
{
	char		*temp;
	
	is_builtin(c);
	if (!c->full_path)
		is_bin(m, c);
	if (c->full_path)
	{
		temp = ft_strjoin(c->full_path, "/");
		c->full_path = ft_strjoin(temp, c->cmd[0]);
		free(temp);
	}
	else
		printf("%s: command not found\n", c->cmd[0]);
	execute(m);
	(void)c;
	return (0);
}

int	print_parser(t_shell *minihell)
{
	t_command	*test;
	t_shell		*m;
	int			i;

	m = minihell;
	i = 1;
	while ((t_command *)(m->parser))
	{
		test = (t_command *)(m->parser->content);
		while (*test->cmd)
		{
			printf("CMD %d: %s\n", i, *test->cmd);
			test->cmd++;
		}
		printf("CMD %d path: %s\n", i, test->full_path);
		if (test->cmd_splitter == PIPE)
			printf("CMD %d splitter: PIPE\n", i);
		else if (test->cmd_splitter == OR)
			printf("CMD %d splitter: OR\n", i);
		else if (test->cmd_splitter == AND)
			printf("CMD %d splitter: AND\n", i);
		m->parser = m->parser->next;
		i++;
	}
	return (0);
}
