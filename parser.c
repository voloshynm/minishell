/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:47:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/09/12 17:09:20 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

t_parser	*init_parser(t_lexer **lexer)
{
	t_lexer	*l;

	l = get_first_token(*lexer);
	if (l->token == PIPE)
	{
		printf("Parse error near '|'\n");
		exit(EXIT_FAILURE);
	}
	while (l)
	{
		if (l->token == PIPE)
	}
}