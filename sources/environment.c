/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:03:31 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/30 23:17:34 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_envp(t_shell *m, char **envp_arg)
{
	char	**v;
	char	**envp_arg_s;
	int		n;

	envp_arg_s = envp_arg;
	n = sizeof_2d_array(envp_arg_s);
	v = (char **)malloc((n + 1) * sizeof(char *));
	if (v == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
	m->envp = v;
	while (*envp_arg_s)
	{
		*v = ft_strdup(*envp_arg_s);
		v++;
		envp_arg_s++;
	}
	*v = NULL;
	//ft_str_bubble_sort(m->envp, n);
	return (0);
}

int	add_to_envp(t_shell *m, char *key_value)
{
	char	**v;
	char	**v_start;
	int		n;

	if (!is_valid_key_value(key_value))
		return (INVAL_ENV_VAR);
	n = sizeof_2d_array(m->envp);
	v = (char **)malloc((n + 2) * sizeof(char *));
	if (v == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
	v_start = v;
	while (*m->envp)
		*(v++) = *(m->envp++);
	*(v++) = ft_strdup(key_value);
	*v = NULL;
	free(m->envp - n);
	m->envp = v_start;
	//ft_str_bubble_sort(m->envp, n + 1);
	return (0);
}

int	update_var_in_envp(t_shell *m, char *key_value)
{
	char	*key;
	char	*value;
	char	**envp;

	key = get_key(key_value);
	value = get_value(key_value);
	envp = m->envp;
	while (*envp && value)
	{
		if (!ft_strncmp(key, *(envp++), ft_strlen(key)))
		{
			free(value);
			value = ft_strdup(*(envp - 1));
			rm_from_envp(m, value);
			add_to_envp(m, key_value);
			free(key);
			free(value);
			return (OK);
		}
	}
	if (value)
		add_to_envp(m, key_value);
	free(key);
	free(value);
	return (OK);
}

int	rm_from_envp(t_shell *m, char *key_value)
{
	char	**v;
	int		n;
	int		nmb;
	int		i;
	int		j;

	n = sizeof_2d_array(m->envp);
	nmb = get_key_nmb(m->envp, key_value);
	if (nmb == -1)
		return (0);
	v = (char **)malloc((n) * sizeof(char *));
	i = -1;
	j = 0;
	while (m->envp[++i])
	{
		if (i != nmb)
			v[j++] = m->envp[i];
		else
			free(m->envp[i]);
	}
	v[j] = NULL;
	free(m->envp);
	m->envp = v;
	//ft_str_bubble_sort(m->envp, sizeof_2d_array(m->envp));
	return (0);
}
