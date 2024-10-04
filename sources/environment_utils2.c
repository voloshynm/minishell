/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:58:30 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/04 16:02:49 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_key_nmb(t_shell *m, char *key_value)
{
	int	len;
	int	nmb;

	len = ft_strlen(key_value);
	nmb = -1;
	while (m->envp[++nmb])
	{
		if (!ft_strncmp(m->envp[nmb], key_value, len))
			return (nmb);
	}
	return (0);
}

char	*get_key(char *key_value)
{
	char	*key;
	int		i;

	i = 0;
	while (key_value[i] && key_value[i] != '=')
		i++;
	key = ft_strndup(key_value, i);
	if (!key)
	{
		p_error(ALLOC_FAILURE, NULL);
		return (NULL);
	}
	return (key);
}

char	*get_value(char *key_value)
{
	char	*value;
	int		i;
	bool	has_equal_sign;
	int		len;

	len = ft_strlen(key_value);
	i = 0;
	has_equal_sign = false;
	while (key_value[i] && !has_equal_sign)
	{
		if (key_value[i] == '=')
			has_equal_sign = true;
		i++;
	}
	if (!has_equal_sign || (has_equal_sign && !key_value[i]))
		return (NULL);
	value = ft_strndup(key_value + i, len - i);
	return (value);
}

int	is_valid_key_value(const char *key_value)
{
	char	*s;

	s = (char *)key_value;
	if (!ft_isalpha(*s))
		return (0);
	s++;
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '=')
			return (0);
		s++;
	}
	return (1);
}

int	is_var_in_envp(t_shell *m, char *key_value)
{
	char	*key;
	char	**envp;

	key = get_key(key_value);
	if (!key)
		return (ALLOC_FAILURE);
	envp = m->envp;
	while (*envp)
	{
		if (!ft_strncmp(key, *envp, ft_strlen(key)))
		{
			free(key);
			return (1);
		}
		envp++;
	}
	free(key);
	return (0);
}
