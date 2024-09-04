/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/04 15:06:13 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_var(t_shell *m)
{
	m->input = NULL;
	m->lexer = NULL;
}

void	free_tokens(t_shell *m)
{
	t_lexer *temp;

	free(m->input);
	while (m->lexer)
	{
		temp = m->lexer;
		m->lexer = m->lexer->next;
		free(temp->str);
		free(temp);
	}
}

void	prompt_loop(t_shell *m)
{
	int count = 0;

	while (count < 2)
	{
		m->input = readline(PROMPT);
		add_history(m->input);
		parse_input(m);
		free_tokens(m);
		count++;
	}
	rl_clear_history();
}

int	main(void)
{
	t_shell	m;

	init_var(&m);
	prompt_loop(&m);
	return (0);
}
