/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:03:19 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:34:07 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strlcat function appends the string src to the end of dst,
* and returns the total length of the resulting string.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	remaining_space;

	dst_len = 0;
	while (dst[dst_len] != 0 && dst_len < size)
		dst_len++;
	remaining_space = size - dst_len;
	if (remaining_space == 0 || size == 0)
		return (dst_len + ft_strlen(src));
	i = 0;
	while (src[i] != 0 && i < remaining_space - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = 0;
	return (dst_len + ft_strlen(src));
}
