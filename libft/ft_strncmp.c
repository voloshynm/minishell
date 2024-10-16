/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:23:15 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:35:22 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strncmp function compares the first n bytes of the string s1 and s2.
* It returns an integer less than, equal to, or greater than zero, 
* according to whether the string s1 is lexicographically less than, 
* to, or greater than the string s2.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*p1 == 0 && *p2 == 0)
			return (0);
		else if (*p1 == 0)
			return (-1);
		else if (*p2 == 0)
			return (1);
		if (*p1 != *p2)
		{
			if (*p1 > *p2)
				return (1);
			if (*p1 < *p2)
				return (-1);
		}
		p1++;
		p2++;
		n--;
	}
	return (0);
}
