#include "includes/executor.h"

int	excecute(t_exec *exec)
{
    pid_t	pid;
    int     status;

    char *const argv[] = {
        "echo",          // argv[0]: program name
        "hello world",   // argv[2]: text to print
        NULL             // Must be terminated by NULL
    };

    pid = fork();
    if (pid == 0) // Child process
    {
        execve(exec->pathname, argv, NULL);
        perror("execve failed");
        exit(1);
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
    {
        perror("fork failed");
        return -1;
    }
    return 1;
}

char	*builtin_exists(t_exec *exec)
{
	DIR				*directory;
	struct dirent	*entry;
	char			path[PATH_MAX];
	char			*pathname;

	getcwd(path, sizeof(path));
	pathname = ft_strjoin(path, "/builtins");
	directory = opendir(pathname);
	while (directory)
	{
		entry = readdir(directory);
		if (!entry)
			break ;
		if (!ft_strncmp(exec->argv[0], entry->d_name, ft_strlen(exec->argv[0])))
		{
			closedir(directory);
			return (pathname);
		}
	}
	closedir(directory);
	free(pathname);
	return (NULL);
}

char	*bin_builtin_exists(t_exec *exec)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	i = 0;
	while (exec->env_path[i])
	{
		directory = opendir(exec->env_path[i]);
		while (directory)
		{
			entry = readdir(directory);
			if (!entry)
				break ;
			if (!ft_strncmp(exec->argv[0], entry->d_name,
					ft_strlen(exec->argv[0])))
			{
				closedir(directory);
				return (exec->env_path[i]);
			}
		}
		closedir(directory);
		i++;
	}
	return (NULL);
}

int	command_exists(t_exec *exec)
{
	char	*temp;

	exec->argv = malloc(sizeof(char *));
	exec->argv[0] = ft_strdup("echo");
	exec->pathname = builtin_exists(exec);
	if (!exec->pathname)
		exec->pathname = bin_builtin_exists(exec);
	if (exec->pathname)
	{
		temp = ft_strjoin(exec->pathname, "/");
		exec->pathname = ft_strjoin(temp, exec->argv[0]);
		free(temp);
	}
	else
		printf("%s: command not found\n", exec->argv[0]);
	excecute(exec);
	return (1);
}
