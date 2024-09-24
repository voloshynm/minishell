/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/24 19:41:30 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		g_sig;

void	init_shell_vars(t_shell *m)
{
	m->envp = ft_split(getenv("PATH"), ':');
	m->pwd = getenv("PWD");
	m->oldpwd = getenv("OLDPWD");
	m->lexer = NULL;
	m->parser = NULL;
	m->input = NULL;
	m->pid = getpid();
	m->ex_status = 0;
	m->pipefd[0] = 0;
	m->pipefd[1] = 1;
	m->last_splitter_token = NONE;
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
		if (*m->input == 0)
			continue ;
		add_history(m->input);
		if (!init_lexer(&m->lexer, m->input))
			parse_commands(m);
		executor_loop(m);
		free_lexer(&m->lexer);
		free_parser(&m->parser);
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