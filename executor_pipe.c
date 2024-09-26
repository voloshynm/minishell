#include "includes/minishell.h"

// (c == 'S') Set all pipes
// (c == 'C') Close all pipe file descriptors in child or parent
static int	set_close_pipe(int num_pipes, int pipes[], char c)
{
	int		i;
	
	i = -1;
	if (c == 'S')
	{
		while (++i < num_pipes)
		{
			if (pipe(pipes + i * 2) == -1)
				return (-1);
		}
		printf("NUmber of pipes created in set_close_pipe: %d\n", i+1);
	}
	if (c == 'C')
	{
		while (++i < 2 * num_pipes)
		close(pipes[i]);
	}
	return (0);
}

// (1) Child cmd_index: Input redirected from pipe cmd_index - 1
// If not the first command, get input from the previous pipe
// (2) Child cmd_index: Output redirected to pipe cmd_index
// If not the last command, output to the next pipe
// (3) Close pipes
static int	upd_fd(int *cmd_index, int pipes[], t_list **current, int num_pipes)
{
	if (*cmd_index > 0)
	{
		printf("dup2: Redirecting pipe for stdin from pipe[%d]\n", (*cmd_index - 1) * 2);
		if (dup2(pipes[(*cmd_index - 1) * 2], STDIN_FILENO) == -1)
			return (p_error2("dup2", NULL));
	}
	if ((*current)->next && ((t_command *)((*current)->content))->cmd_splitter == PIPE)
	{
		printf("dup2: Redirecting pipe for stdout to pipe[%d]\n", *cmd_index * 2 + 1);
		if (dup2(pipes[*cmd_index * 2 + 1], STDOUT_FILENO) == -1)
			return (p_error2("dup2", NULL));
	}
	set_close_pipe(num_pipes, pipes, 'C');
	return (0);
}
static void iterate_cmd(t_list	**p, int *cmd_index)
{
	*p = (*p)->next;
	(*cmd_index)++;
}

// PID Array: created to store the PIDs of each child process as they are forked
// Storing PIDs: Each time call fork(), store the resulting PID in the pids array
int execute_pipe(t_shell *m, t_list **p, int num_pipes, int i)
{
	pid_t	pids[num_pipes + 1];
	int		pipes[2 * num_pipes];

	if (set_close_pipe(num_pipes, pipes, 'S') == -1)
		return (p_error2("pipe", NULL));
	while (p && i < num_pipes + 1)
	{
		t_command *c = (t_command *)((*p)->content);
		pids[i] = fork();
		if (pids[i] == -1)
			return (p_error2("fork", NULL));
		if (pids[i] == 0)
		{
			if (upd_fd(&i, pipes, p, num_pipes) || setup_redirection(c, m))
				return (errno);
			execve(c->full_path, c->cmd, NULL);
			exit(p_error2("execve", NULL));
		}
		iterate_cmd(p, &i);
	}
	set_close_pipe(num_pipes, pipes, 'C');
	wait_children(m, num_pipes, pids);
	return (0);
}