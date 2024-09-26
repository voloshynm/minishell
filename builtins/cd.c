/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:13 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/26 21:45:52 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	// Check for the correct number of arguments
	if (argc < 2 || argc > 2)
	{ // Expecting exactly one argument (the directory path)
		fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	// Attempt to change the directory
	if (chdir(argv[1]) == -1)
	{
		perror("cd failed"); // Use perror to print the error message
		return (EXIT_FAILURE);
	}

	// Successful change of directory
	return (EXIT_SUCCESS);
}