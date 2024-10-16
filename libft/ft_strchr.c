/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:41:30 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:32:39 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strchr function locates the first occurrence of the character c in the
* string pointed to by s.
*/
char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (unsigned char)c)
			return (p);
		p++;
	}
	if (*p == (unsigned char)c)
		return (p);
	return (NULL);
}
