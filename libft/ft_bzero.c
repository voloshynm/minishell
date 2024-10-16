/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:52:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:17:09 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*The ft_bzero function sets a specified number of bytes
* in a memory area to zero.
*/
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*pointer;

	pointer = s;
	while (n > 0)
	{
		*pointer = (unsigned char) 0;
		pointer++;
		n--;
	}
}
