/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/18 16:32:33 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_minishell(t_shell *m)
{
	m->input = NULL;
	m->lexer = NULL;
	m->parser = NULL;
	m->input = NULL;
	m->pid = getpid();
	m->ex_status = 0;
}

int	input_error(char *input)
{
	char	token_type;

	while (1)
	{
		input = ft_strpbrk(input, "|&<>");
		if (input)
			token_type = *input;
		if (!input)
			break ;
		if (*(++input) == ' ' || *input == '\t')
		{
			while (*input == ' ' || *input == '\t' && *input)
				input++;
			if (*input == token_type)
				return (p_error(2, &token_type));
		}
	}
	return (0);
}

void	prompt_loop(t_shell *m)
{
	int	status;

	while (1)
	{
		m->input = readline(PROMPT);
		init_lexer(m->lexer, m->input);
		add_history(m->input);
		// command_exists(&m->exec);
		free(m->input);
		// free_lexer(m->lexer);
		// free(m->exec->argv[0]);      ////TEST
		// free(m->exec->argv);         ////TEST
	}
	rl_clear_history();
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	t_shell m;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_var(&m);
	prompt_loop(&m);
	return (0);
}