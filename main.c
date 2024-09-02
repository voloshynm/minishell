/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/02 15:08:01 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_var(t_shell *m)
{
	m->alloc = NULL;
	m->input = NULL;
	m->lexer = NULL;
}

void	prompt_loop(t_shell *m)
{
	char	**tokens;
	int		x;

	while (1)
	{
		x = 0;
		m->input = readline(PROMPT);
		add_history(m->input);
		parse_input(m);
		// gc(&m->alloc);
		free(m->input);
	}
	rl_clear_history();
}

int	main(void)
{
	t_shell	m;

	init_var(&m);
	prompt_loop(&m);
	// gc(&m.alloc);
	return (0);
}
