/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:08:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/30 22:56:21 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_path_var(t_shell *m)
{
	char	*paths;
	char	**envp;
	int		key_index;

	envp = m->envp;
	if (m->envpath && *m->envpath)
		free_ft_split(m->envpath);
	key_index = get_key_nmb(envp, "PATH");
	if (key_index >= 0)
		paths = get_value(envp[key_index]);
	if (key_index < 0 || !paths)
	{
		m->envpath = NULL;
		return ;
	}
	m->envpath = ft_split(paths, ':');
	free(paths);
}

int	is_builtin(t_command *c)
{
	return (!ft_strcmp(c->cmd[0], "cd") || !ft_strcmp(c->cmd[0], "pwd")
		|| !ft_strcmp(c->cmd[0], "echo") || !ft_strcmp(c->cmd[0], "export")
		|| !ft_strcmp(c->cmd[0], "env") || !ft_strcmp(c->cmd[0], "unset")
		|| !ft_strcmp(c->cmd[0], "exit"));
}

int	is_bin(t_shell *m, t_command *c)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	i = -1;
	update_path_var(m);
	while (m->envpath && m->envpath[++i])
	{
		directory = opendir(m->envpath[i]);
		while (directory)
		{
			entry = readdir(directory);
			if (!entry)
				break ;
			if (!ft_strcmp(c->cmd[0], entry->d_name))
			{
				c->full_path = ft_strdup(m->envpath[i]);
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
	struct stat	s;

	if (c->cmd[0] == NULL)
		return (1);
	if (!is_builtin(c))
	{
		if (is_bin(m, c) && c->full_path)
		{
			temp = ft_strjoin(c->full_path, "/");
			free(c->full_path);
			c->full_path = ft_strjoin(temp, c->cmd[0]);
			free(temp);
		}
		if (!stat(c->cmd[0], &s) && ft_strchr(c->cmd[0], '/'))
		{
			if (S_ISDIR(s.st_mode))
				return (0);
			if (access(c->cmd[0], X_OK) == 0)
				c->full_path = ft_strdup(c->cmd[0]);
		}
	}
	return (0);
}

char	*copy_char(char c)
{
	char	*new_str;

	new_str = (char *)malloc(2 * sizeof(char));
	if (!new_str)
		return NULL;
	new_str[0] = c;
	new_str[1] = '\0';
	return (new_str);
}

//! DEBUGGING
// int	print_parser(t_shell *minihell)
// {
// 	t_command	*test;
// 	t_shell		*m;
// 	int			i;

// 	m = minihell;
// 	i = 1;
// 	while ((t_command *)(m->parser))
// 	{
// 		printf("Node %d\n", i);
// 		test = (t_command *)(m->parser->content);
// 		while (*test->cmd)
// 		{
// 			printf("CMD %d: %s\n", i, *test->cmd);
// 			test->cmd++;
// 		}
// 		printf("CMD %d path: %s\n", i, test->full_path);
// 		if (test->cmd_splitter == PIPE)
// 			printf("CMD %d splitter: PIPE\n", i);
// 		else if (test->cmd_splitter == OR)
// 			printf("CMD %d splitter: OR\n", i);
// 		else if (test->cmd_splitter == AND)
// 			printf("CMD %d splitter: AND\n", i);
// 		m->parser = m->parser->next;
// 		i++;
// 	}
// 	return (0);
// }
