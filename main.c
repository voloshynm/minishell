/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/08/29 18:18:12 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_var(t_shell *m)
{
	m->alloc = NULL;
	m->input = NULL;
}

void	prompt_loop(t_shell *m)
{
	char	**tokens;
	int i;

	while (1)
	{
		m->input = readline(PROMPT);
		add_history(m->input);
		tokens = ft_split(m->input, ' ');
		free(m->input);
		parse_input(tokens);
		while (tokens[i])
			add_gc_node(&(m->alloc), tokens[i++]);
		free(tokens);
	}
	rl_clear_history();
}

int	main(void)
{
	t_shell	m;

	init_var(&m);
	prompt_loop(&m);
	gc(&m.alloc);
	return (0);
}
