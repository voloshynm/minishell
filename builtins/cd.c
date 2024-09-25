/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/25 13:36:06 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (chdir(argv[1]) == -1)
			printf("cd: %s: No such file or directory\n", argv[1]);
	}
	if (argc == 3)
		printf("cd: string not in pwd: %s\n", argv[1]);
	return (0);
}
