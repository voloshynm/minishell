#include "includes/minishell.h"

static int	is_valid_key_value(const char* key_value)
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

int init_envp(t_shell *m, char **envp_arg)
{
	char	**v;
	int		n;

	n = sizeof_2d_array(envp_arg);
	v = (char **)malloc((n + 1) * sizeof(char *));
	if (v == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
	m->envp = v;
	while (*envp_arg)
	{
		*v = ft_strdup(*envp_arg);
		v++;
		envp_arg++;
	}
	*v = NULL;
	ft_str_bubble_sort(m->envp, n);
	return (0);
}

int add_to_envp(t_shell *m, char *key_value)
{
	char	**v;
	char	**v_start;
	int		n;

	if (!is_valid_key_value(key_value))
		return (p_error(INVAL_ENV_VAR, NULL));
	n = sizeof_2d_array(m->envp);
	v = (char **)malloc((n + 2) * sizeof(char *));
	if (v == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
	v_start = v;
	while (*m->envp)
		*(v++) = *(m->envp++);
	*(v++) = ft_strdup(key_value);
	(v++);
	*v = NULL;
	free(m->envp - n);
	m->envp = v_start;
	ft_str_bubble_sort(m->envp, n + 1);
	return (0);
}

void	print_envp(t_shell *m)
{
	char	**v;

	v = m->envp;
	while (*v)
		printf("%s\n", *(v++));
}

int	get_key_nmb(t_shell *m, char *key_value)
{
	int		len;
	int		nmb;

	len = ft_strlen(key_value);
	nmb = -1;
	while (m->envp[++nmb])
	{
		if (!ft_strncmp(m->envp[++nmb], key_value, len))
			return(nmb);
	}
	return (0);
}

int	rm_from_envp(t_shell *m, char *key_value)
{
	char	**v;
	int		n;
	int		nmb;
	int		i;

	n = sizeof_2d_array(m->envp);
	v = (char **)malloc((n) * sizeof(char *));
	if (v == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
	nmb = get_key_nmb(m, key_value);
	i = -1;
	while (m->envp[++i] && i < nmb)
		v[i] = m->envp[i];
	while (m->envp[++i] && i < n)
		v[i] = m->envp[i];
	v[i] = NULL;
	free(m->envp - n);
	m->envp = v;
	ft_str_bubble_sort(m->envp, n);
	return (0);
}