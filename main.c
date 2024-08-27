/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/08/27 22:37:23 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void prompt_loop(shell_t *m)
{
	while (true)
	{
		m->input = readline(PROMPT);
	}
}

int	main(void)
{
	shell_t m;

    prompt_loop(&m);
    return 0;
}