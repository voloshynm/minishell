/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:33:36 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 23:38:48 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The ft_strpbrk function locates the first occurrence in the string s of any
 * character that matches any character in the string c.
 */
char	*ft_strpbrk(const char *s, const char *c)
{
	const char	*str;
	int			i;

	str = (const char *)s;
	if (!s || !c)
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
