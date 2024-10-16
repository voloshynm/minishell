/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:44:54 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:28:21 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_memcpy function copies n bytes from memory area src to area dest.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*t_dest;
	const unsigned char	*t_src;

	t_dest = dest;
	t_src = src;
	while (n != 0)
	{
		*t_dest++ = *t_src++;
		n--;
	}
	return (dest);
}
