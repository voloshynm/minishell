/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:19:38 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/21 21:06:02 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_sig_pid == 0 || g_sig_pid == 1 || g_sig_pid == 2)
		rl_redisplay();
}

// ioctl(0, TIOCSTI, "\n"); This is to simulate a new line
void	handle_sigint(int code)
{
	(void)code;
	if (g_sig_pid == -255)
	{
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
	else
	{
		write(1, "\n", 1);
		clear_rl_line();
	}
	g_sig_pid = 1;
}

void	handle_sigquit(int code)
{
	(void)code;
	write(1, "Quit (core dumped)\n", 20);
	clear_rl_line();
	g_sig_pid = 2;
}

void	handle_signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
