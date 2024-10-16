/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:12:02 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:32:26 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_memcmp function compares byte-by-byte the two memory areas s1 and s2,
* for the first n bytes.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*p1 != *p2)
		{
			if (*p1 > *p2)
				return (1);
			else if (*p1 < *p2)
				return (-1);
		}
		p1++;
		p2++;
		n--;
	}
	return (0);
}
