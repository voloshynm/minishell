/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/29 19:21:05 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig_pid;

/*
^FIX PIPE SEG FAULT,  last_splitter_token was not being reset,
^reset_vars() now is being called after every main_loop iteration.
& m->exit_statuses[i] = -300 because errors are from 1 to 255 and -1.
& 0 - successfully finished process
*/
void	reset_vars(t_shell *m)
{
	m->lexer = NULL;
	m->parser = NULL;
	m->input = NULL;
	g_sig_pid = m->ex_status;
	m->ex_status = 0;
	m->fork_status = -255;
	m->last_splitter_token = NONE;
	m->pipefd[0] = -255;
	m->pipefd[1] = -255;
}

void	init_shell_vars(t_shell *m, char **envp)
{
	m->envpath = NULL;
	m->original_pwd = ft_strdup(getenv("PWD"));
	if (!m->original_pwd)
		p_error(ALLOC_FAILURE, NULL);
	init_envp(m, envp);
	update_path_var(m);
	m->pwd = ft_strdup(m->original_pwd);
	m->oldpwd = ft_strdup(getenv("OLDPWD"));
	if (!m->oldpwd)
		p_error(ALLOC_FAILURE, NULL);
	m->pid = getpid();
	m->ex_status = 0;
	reset_vars(m);
}

void	prompt_loop(t_shell *m)
{
	char	*input_ptr;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		m->input = readline(PROMPT);
		if (m->input == NULL)
		{
			write(1, "exit\n", 5);
			free_all_resources(m);
			break ;
		}
		input_ptr = m->input;
		add_history(m->input);
		if (!init_lexer(&m->lexer, m->input))
		{
			parse_commands(m, m->lexer);
			executor_loop(m);
			free_parser(&m->parser);
		}
		free_lexer(&m->lexer);
		reset_vars(m);
		free(input_ptr);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	m;

	(void)argv;
	if (argc != 1)
	{
		printf("Minishell cannot be launched with arguments\n");
		return (EXIT_FAILURE);
	}
	handle_signals();
	init_shell_vars(&m, envp);
	prompt_loop(&m);
	return (0);
}
