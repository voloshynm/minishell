/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:12:31 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/29 19:32:21 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_inv_c_pipe(t_shell *m, t_list **p)
{
	t_command	*c;
	bool		is_invalid;

	is_invalid = false;
	c = ((t_command *)((*p)->content));
	if (!c->cmd[0] || !c->cmd[0][0])
		return (1);
	if (c->full_path == NULL && !is_builtin(c))
	{
		if (!is_invalid)
			printf("%s: command not found\n", c->cmd[0]);
		is_invalid = true;
	}
	if (*p && (*p)->next && is_invalid)
		*p = (*p)->next;
	if (is_invalid)
		m->ex_status = CMD_NOT_EXIST;
	return (is_invalid);
}

int	get_cmd_len(t_lexer *lexer)
{
	int		len;
	int		redir;
	t_lexer	*l;

	l = lexer;
	len = 0;
	redir = 0;
	while (l && !is_token_pipish(l))
	{
		if (is_token_redir(l))
			redir += 2;
		len++;
		l = l->next;
	}
	return (len);
}

int	process_env_args(t_shell *m, t_command **c)
{
	int		i;

	i = -1;
	while ((*c)->cmd[++i])
	{
		if (ft_strchr((*c)->cmd[i], '$') && *((*c)->q_type[i]) != '\'')
		{
			process_env_arg(&((*c)->cmd[i]), &m->envp);
			if (ft_strlen((*c)->cmd[i]) == 0)
				rmv_cmd(c, i, NULL, NULL);
		}
	}
	return (0);
}

void	rmv_cmd(t_command **c, int i, char **new_cmd, char **new_q_type)
{
	int			j;
	char		**new_cmd_start;
	char		**new_q_start;

	j = 0;
	while ((*c)->cmd[j])
		j++;
	new_cmd = ft_calloc(j - 1 + 1, sizeof(char *));
	new_q_type = ft_calloc(j - 1 + 1, sizeof(char *));
	new_cmd_start = new_cmd;
	new_q_start = new_q_type;
	j = -1;
	while ((*c)->cmd[++j])
	{
		if (j != i)
		{
			*(new_cmd) = ft_strdup((*c)->cmd[j]);
			*(new_q_type) = ft_strdup((*c)->q_type[j]);
			new_cmd++;
			new_q_type++;
		}
	}
	free_cmds(c);
	(*c)->cmd = new_cmd_start;
	(*c)->q_type = new_q_start;
}
