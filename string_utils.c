/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:11:19 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/23 14:04:50 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strpbrk(const char *s, const char *c)
{
	const char	*str = s;
	int			i;

	if (!str)
		return (NULL);
	while (*str)
	{
		i = 0;
		while (c[i])
		{
			if (*str == c[i])
				return ((char *)str);
			i++;
		}
		str++;
	}
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*t_s;
	char	*new_str;
	char	*start;

	t_s = (char *)s;
	i = 0;
	new_str = malloc((n + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*t_s && i < n)
	{
		*new_str = *t_s;
		new_str++;
		t_s++;
		i++;
	}
	*new_str = 0;
	return (start);
}

/*
**	Removes first quote str[0] from a string used
	to determinate the token type
*/
char	*remove_first_char(char *str)
{
	char	*old_str;
	char	*new_str;

	old_str = str;
	new_str = ft_strdup(++old_str);
	free(--old_str);
	return (new_str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (*p1 != '\0' || *p2 != '\0')
	{
		if (*p1 > *p2)
			return (1);
		else if (*p1 < *p2)
			return (-1);
		p1++;
		p2++;
	}
	return (0);
}