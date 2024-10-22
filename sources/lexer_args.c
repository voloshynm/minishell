/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:51:35 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/22 18:31:19 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function to replace the environment variable in str with its value
** s is the pointer after the '$', so it's the start of the variable name
** Find the end of the variable name (assumed to be alphanum or underscores)
** Extract the variable name
** Find the corresponding value in envp
** Allocate space for the new string
** Copy the part before the variable
** -1 to account for the '$'
** Copy the environment value
** Copy the remaining part of the string after the variable
*/
static char	*replace_real_arg(char *s, char *str, char ***envp)
{
	char	*v_st;
	char	*v_end;
	char	*result;
	char 	*var_name;
	char 	*env_val;
	
	v_st = s;
	v_end = s;
	while (*v_end && (ft_isalnum(*v_end) || *v_end == '_'))
		v_end++;
	var_name = ft_strndup(v_st, v_end - v_st);
	env_val = get_env_value(var_name, envp);
	free(var_name);
	result = malloc(ft_strlen(str) - (v_end - v_st) + ft_strlen(env_val) + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, (s - str - 1));
	ft_strcpy(result + (s - str - 1), env_val);
	ft_strcpy(result + (s - str - 1) + ft_strlen(env_val), v_end);
	return (result);
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
	free(tmp_2);
	tmp_2 = ft_strndup(str, ft_strlen(str) - ft_strlen(start) - 1);
	if (tmp_1 == NULL || tmp_2 == NULL)
		return (NULL);
	new_str = ft_strjoin(tmp_2, tmp_1);
	free(tmp_1);
	free(tmp_2);
	return (new_str);
}

static char	*replace_env_arg(char *s, char *str, char ***envp)
{
	char	*new_str;

	if (ft_isdigit(*s))
		new_str = replace_digit(s, str);
	else if (*s == '?')
		new_str = replace_quest_mark(s, str);
	else
		new_str = replace_real_arg(s, str, envp);
	free(str);
	return (new_str);
}

int	process_env_arg(char **str, char ***envp)
{
	int		qt[2];
	char	*s;

	qt[0] = 0;
	qt[1] = 0;
	s = *str;
	while (*s)
	{
		if ((*s == '\'' && !qt[1]) || (*s == '\"' && !qt[0]))
		{
			qt[0] ^= (*s == '\'');
			qt[1] ^= (*s == '\"');
			s++;
			continue ;
		}
		if (!qt[0] && *s == '$' && (ft_isalnum(*(s + 1)) || *(s + 1) == '?'))
		{
			*str = replace_env_arg(++s, *str, envp);
			s = *str;
			if (!s || !ft_strchr(*str, '$'))
				break ;
		}
		s++;
	}
	return (OK);
}
