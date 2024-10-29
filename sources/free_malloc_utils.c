/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:26:20 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/29 19:26:22 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*token;

	if (lexer == NULL || *lexer == NULL)
		return ;
	while (*lexer)
	{
		token = get_first_token(*lexer);
		if (token == NULL)
			return ;
		*lexer = token->next;
		if (*lexer)
			(*lexer)->prev = NULL;
		if (token->str)
			free(token->str);
		token->str = NULL;
		token->q_type = 0;
		free(token);
		token = NULL;
	}
	*lexer = NULL;
}

void	free_parser(t_list **parser)
{
	t_list		*p;
	t_command	*command;
	int			i;

	if (parser == NULL)
		return ;
	while (*parser)
	{
		p = *parser;
		*parser = (*parser)->next;
		command = ((t_command *)p->content);
		i = 0;
		while (command->cmd && command->cmd[i])
		{
			free(command->q_type[i]);
			free(command->cmd[i++]);
		}
		free(command->cmd);
		free(command->q_type);
		free(command->full_path);
		free(command->input_path);
		free(command);
		free(p);
	}
	*parser = NULL;
}

void	free_cmds(t_command **c)
{
	int	j;

	j = -1;
	while ((*c)->cmd[++j])
	{
		free((*c)->q_type[j]);
		free((*c)->cmd[j]);
	}
	free((*c)->cmd);
	free((*c)->q_type);
}

void	free_all_resources(t_shell *m)
{
	free_parser(&m->parser);
	free_lexer(&m->lexer);
	free_ft_split(m->envp);
	if (m->envpath && *m->envpath)
		free_ft_split(m->envpath);
	free(m->original_pwd);
	if (m->pwd)
		free(m->pwd);
	free(m->oldpwd);
	m->lexer = NULL;
	m->parser = NULL;
	m->input = NULL;
	m->envpath = NULL;
	m->original_pwd = NULL;
	m->oldpwd = NULL;
	m->pid = 0;
	rl_clear_history();
}
