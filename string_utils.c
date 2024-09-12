/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:11:19 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/12 10:11:52 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strpbrk(const char *s, const char *c)
{
	const char	*str = s;
	int			i;

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