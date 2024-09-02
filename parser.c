/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/02 15:23:14 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_token_list(t_shell *m)
{

}

void	extract_token(t_shell *m)
{
	char	*str;
	char	*start;
	int		length;

	while (m->input)
	{
		start = m->input;
		m->input = ft_strchr(m->input, ' ');
		if (m->input)
			length = (start - m->input++) * -1;
		else
			length = ft_strlen(start);
		str = ft_malloc(&m->alloc, sizeof(char) * length + 1);
		ft_strlcpy(str, start, length + 1);
	}
}

void	parse_input(t_shell *m)
{
	if (m->input == NULL)
		return ;
	extract_token(m);
}