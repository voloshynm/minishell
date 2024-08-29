/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/08/29 21:38:40 by sandre-a         ###   ########.fr       */
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
 
	while (1)
	{
		m->input = readline(PROMPT);
		add_history(m->input);
		free(m->input);
		char *str = ft_strdup("hey");
		parse_input(m); 
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
