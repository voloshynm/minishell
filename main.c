/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/20 10:52:09 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	initialize_vars(t_shell *m)
{
	m->envp = ft_split(getenv("PATH"), ':'),
	m->input = NULL;
	m->lexer = NULL;
	m->parser = NULL;
	m->input = NULL;
	m->pid = getpid();
	m->ex_status = 0;
}

int	input_error(char *input)
{
	char	token_type;

	while (1)
	{
		input = ft_strpbrk(input, "|&<>");
		if (input)
			token_type = *input;
		if (!input)
			break ;
		if (*(++input) == ' ' || *input == '\t')
		{
			while (*input == ' ' || (*input == '\t' && *input))
				input++;
			if (*input == token_type)
				return (p_error(2, &token_type));
		}
	}
	return (0);
}

void	prompt_loop(t_shell *m)
{
	while (1)
	{
		m->input = readline(PROMPT);
		if (m->input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*m->input == 0)
			continue ;
		add_history(m->input);
		if (!init_lexer(&m->lexer, m->input))
			parse_commands(m);
		// command_exists(m);
		free(m->input);
		free_lexer(&m->lexer);
		free_parser(&m->parser);
		// free(m->exec->argv[0]);      ////TEST
		// free(m->exec->argv);         ////TEST
	}
	rl_clear_history();
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv)
{
	t_shell m;

	(void)argv;
	if (argc != 1)
	{
		printf("Minishell cannot be launched with arguments\n");
		return (EXIT_FAILURE);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	initialize_vars(&m);
	prompt_loop(&m);
	return (0);
}