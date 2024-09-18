// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/17 19:14:56 by sandre-a          #+#    #+#             */
// /*   Updated: 2024/09/18 21:32:51 by sandre-a         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "includes/minishell.h"

// int	excecute(t_exec *exec)
// {
// 	pid_t	pid;
// 	int		status;

// 	char *const argv[] = {
// 		"find", // argv[0]: program name
// 		"/",    // argv[2]: text to print
// 		"*",
// 		NULL // Must be terminated by NULL
// 	};
// 	pid = fork();
// 	if (pid == 0) // Child process
// 	{
// 		execve(exec->pathname, argv, NULL);
// 		perror("execve failed");
// 		exit(1);
// 	}
// 	else if (pid > 0)
// 		waitpid(pid, &status, 0);
// 	else
// 	{
// 		perror("fork failed");
// 		return (-1);
// 	}
// 	return (1);
// }

// char	*builtin_exists(t_shell *m)
// {
// 	DIR				*directory;
// 	struct dirent	*entry;
// 	char			path[PATH_MAX];
// 	char			*pathname;

// 	getcwd(path, sizeof(path));
// 	pathname = ft_strjoin(path, "/builtins");
// 	directory = opendir(pathname);
// 	while (directory)
// 	{
// 		entry = readdir(directory);
// 		if (!entry)
// 			break ;
// 		if (!ft_strncmp(m->exec->argv[0], entry->d_name,
// 				ft_strlen(m->exec->argv[0])))
// 		{
// 			closedir(directory);
// 			return (pathname);
// 		}
// 	}
// 	closedir(directory);
// 	free(pathname);
// 	return (NULL);
// }

// char	*bin_builtin_exists(t_shell *m)
// {
// 	DIR				*directory;
// 	struct dirent	*entry;
// 	int				i;

// 	i = 0;
// 	while (m->envp[i])
// 	{
// 		directory = opendir(m->envp[i]);
// 		while (directory)
// 		{
// 			entry = readdir(directory);
// 			if (!entry)
// 				break ;
// 			if (!ft_strncmp(m->exec->argv[0], entry->d_name,
// 					ft_strlen(m->exec->argv[0])))
// 			{
// 				closedir(directory);
// 				return (m->envp[i]);
// 			}
// 		}
// 		closedir(directory);
// 		i++;
// 	}
// 	return (NULL);
// }

// int	command_exists(t_shell *m)
// {
// 	char	*temp;

// 	m->envp = ft_split(getenv("PATH"), ':');
// 	m->exec->argv = malloc(sizeof(char *));
// 	m->exec->argv[0] = ft_strdup("find");
// 	m->exec->pathname = builtin_exists(m);
// 	if (!m->exec->pathname)
// 		m->exec->pathname = bin_builtin_exists(m);
// 	if (m->exec->pathname)
// 	{
// 		temp = ft_strjoin(m->exec->pathname, "/");
// 		m->exec->pathname = ft_strjoin(temp, m->exec->argv[0]);
// 		free(temp);
// 	}
// 	else
// 		printf("%s: command not found\n", m->exec->argv[0]);
// 	excecute(m->exec);
// 	return (1);
// }
