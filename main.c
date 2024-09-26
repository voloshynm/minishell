/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/26 02:10:09 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		g_sig_pid;

/*
^FIX PIPE SEG FAULT,  last_splitter_token was not being reset,
^reset_vars() now is being called after every main_loop iteration.
& m->exit_statuses[i] = -300 because errors are from 1 to 255 and -1.
& 0 - successfully finished process
*/
void	reset_vars(t_shell *m)
{
	int i;

	i = -1;
	m->lexer = NULL;
	m->parser = NULL;
	m->input = NULL;
	g_sig_pid = 0;
	m->ex_status = 0;
	while(++i < MAX_FDS)
		m->exit_statuses[i] = -300;
	m->pipefd[0] = 0;
	m->pipefd[1] = 1;
	m->last_splitter_token = NONE;
}

void	init_shell_vars(t_shell *m)
{
	m->envp = ft_split(getenv("PATH"), ':');
	m->pwd = getenv("PWD");
	m->oldpwd = getenv("OLDPWD");
	m->pid = getpid();
	reset_vars(m);
}

void	prompt_loop(t_shell *m)
{
	while (1)
	{
		m->input = readline(PROMPT);
		if (m->input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcount(m->input, ' ') == (int)ft_strlen(m->input))
			continue ;
		add_history(m->input);
		if (!init_lexer(&m->lexer, m->input))
		{
			if (!parse_commands(m))
				executor_loop(m);
			free_lexer(&m->lexer);
			free_parser(&m->parser);
			reset_vars(m);
		}
	}
	rl_clear_history();
}

int	main(int argc, char **argv)
{
	t_shell m;

	(void)argv;
	if (argc != 1)
	{
		printf("Minishell cannot be launched with arguments\n");
		return (EXIT_FAILURE);
	}
	handle_signals();
	init_shell_vars(&m);
	prompt_loop(&m);
	return (0);
}