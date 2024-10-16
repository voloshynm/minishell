/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:51:35 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/16 22:19:43 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Pointer *s shows start of the name of variable. After moving till the end
	of alphanum. Upon retrieving non-alphanum, it gets the value of variable
	adds whatever left after the name and stores into tmp1. From lexer->str it
	retrieves the chars before $ sign into tmp1. Then it joins tmp2 and tmp1
	in fact replacing the name of variable with the value.
*/
static char	*replace_real_arg(char *s, char *str)
{
	char	*new_str;
	char	*tmp_1;
	char	*tmp_2;
	char	*start;

	start = s;
	if (ft_strcmp(s, "EMPTY") == 0)
		return ("");
	while (ft_isalnum(*s))
		s++;
	tmp_1 = ft_strndup(start, s - start);
	if (tmp_1 == NULL)
		return (NULL);
	tmp_2 = getenv(tmp_1);
	if (!tmp_2)
		tmp_2 = "";
	free(tmp_1);
	tmp_1 = ft_strjoin(tmp_2, s);
	tmp_2 = ft_strndup(str, ft_strlen(str) - ft_strlen(start) - 1);
	if (tmp_1 == NULL || tmp_2 == NULL)
		return (NULL);
	new_str = ft_strjoin(tmp_2, tmp_1);
	free(tmp_1);
	free(tmp_2);
	return (new_str);
}

static char	*replace_digit(char *s, char *str)
{
	char	*new_str;
	char	*tmp_1;
	char	*tmp_2;
	char	*start;

	start = s;
	tmp_1 = s + 1;
	tmp_2 = ft_strndup(str, ft_strlen(str) - ft_strlen(start) - 1);
	if (tmp_1 == NULL || tmp_2 == NULL)
		return (NULL);
	new_str = ft_strjoin(tmp_2, tmp_1);
	free(tmp_2);
	return (new_str);
}

static char	*replace_quest_mark(char *s, char *str)
{
	char	*new_str;
	char	*tmp_1;
	char	*tmp_2;
	char	*start;

	start = s;
	tmp_2 = ft_itoa(g_sig_pid);
	if (!tmp_2)
		tmp_2 = "";
	tmp_1 = ft_strjoin(tmp_2, s + 1);
	tmp_2 = ft_strndup(str, ft_strlen(str) - ft_strlen(start) - 1);
	if (tmp_1 == NULL || tmp_2 == NULL)
		return (NULL);
	new_str = ft_strjoin(tmp_2, tmp_1);
	free(tmp_1);
	free(tmp_2);
	return (new_str);
}

static char	*replace_env_arg(char *s, char *str)
{
	if (ft_isdigit(*s))
		return (replace_digit(s, str));
	else if (*s == '?')
		return (replace_quest_mark(s, str));
	return (replace_real_arg(s, str));
}

int	process_env_arg(char **str)
{
	int		s_qt;
	int		d_qt;
	char	*s;

	s_qt = 0;
	d_qt = 0;
	s = *str;
	while (*s)
	{
		if ((*s == '\'' && !d_qt) || (*s == '\"' && !s_qt))
		{
			s_qt ^= (*s == '\'');
			d_qt ^= (*s == '\"');
			s++;
			continue ;
		}
		if (!s_qt && *s == '$' && (ft_isalnum(*(s + 1)) || *(s + 1) == '?'))
		{
			*str = replace_env_arg(++s, *str);
			if (*str == NULL)
				return (ALLOC_FAILURE);
		}
		s++;
	}
	return (OK);
}
