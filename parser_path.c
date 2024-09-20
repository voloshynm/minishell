/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:08:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/20 12:46:33 by mvoloshy         ###   ########.fr       */
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

int	is_bin(t_shell *m, int i)
{
	DIR				*directory;
	struct dirent	*entry;
	t_command		*p;

	i = 0;
	p = ((t_command *)(m->parser->content));
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

int	parse_full_path(t_command *c, t_shell *m)
{
	char		*temp;
	t_command	*p;
	int			i;

	p = ((t_command *)(m->parser->content));
	i = 0;
	p->full_path = NULL;
	is_builtin(m);
	if (!p->full_path)
		is_bin(m, i);
	if (p->full_path)
	{
		temp = ft_strjoin(p->full_path, "/");
		p->full_path = ft_strjoin(temp, p->cmd[0]);
		free(temp);
	}
	else
		printf("%s: command not found\n", p->cmd[0]);
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
