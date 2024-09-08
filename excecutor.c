/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:06:18 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/04 19:40:25 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void excecute(void)
{
	pid_t pid;
	const char *pathname = "/bin/echo";

    char *const argv[] = {
        "echo",            // argv[0]: The name of the program (conventionally)
        "-n",              // argv[1]: Argument to the program
        "hello world",     // argv[2]: Argument to the program
        NULL               // Must be terminated by NULL
    };

	pid = fork();
	if (pid == 0)
		execve(pathname, argv, NULL);
}