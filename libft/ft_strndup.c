/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:30:53 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 23:32:22 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The strndup function duplicates a string up to a specified number of
 * characters and null-terminates the new string.
 */

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
