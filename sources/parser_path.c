/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:08:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/15 14:55:56 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_command *c)
{
	if (!ft_strcmp(c->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(c->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(c->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(c->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(c->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(c->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(c->cmd[0], "exit"))
		return (1);
	return (0);
}

int	is_bin(t_shell *m, t_command *c)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	i = -1;
	while (m->envpath[++i])
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
	char	*temp;

	if (c->cmd[0] == NULL)
		return (1);
	if (!is_builtin(c))
		is_bin(m, c);
	if (c->full_path)
	{
		temp = ft_strjoin(c->full_path, "/");
		if (!temp)
			return (p_error(ALLOC_FAILURE, NULL));
		free(c->full_path);
		c->full_path = ft_strjoin(temp, c->cmd[0]);
		free(temp);
		if (!c->full_path)
			return (p_error(ALLOC_FAILURE, NULL));
	}
	return (0);
}

void	free_parser(t_list **parser)
{
	t_list		*p;
	t_command	*command;
	int			i;

	if (parser == NULL)
		return ;
	while (*parser)
	{
		p = *parser;
		*parser = (*parser)->next;
		command = ((t_command *)p->content);
		if (command->cmd)
		{
			i = 0;
			while (command->cmd[i])
				free(command->cmd[i++]);
			free(command->cmd);
		}
		free(command->full_path);
		free(command);
		free(p);
	}
	*parser = NULL;
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
