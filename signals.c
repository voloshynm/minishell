/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:19:38 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/26 02:54:50 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void clear_rl_line(void)
{
    rl_replace_line("", 0); 
    rl_on_new_line();        
	if (g_sig_pid == 0 || g_sig_pid == 1)
    	rl_redisplay();        
}

void handle_sigint(int code)
{
	
    (void)code; 
    write(1, "\n", 1); 
    clear_rl_line();    
}

void handle_signals(void)
{
    signal(SIGINT, &handle_sigint);
    signal(SIGQUIT, SIG_IGN);      
}