/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ends_with.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 02:18:06 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/23 02:32:41 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Determines whether the given string ends with a specified substring.
 */
#include "libft.h"

int	ft_str_ends_with(const char *str, const char *end)
{
	int	size;

	if (ft_strlen(str) < ft_strlen(end) || !str || !end)
		return (0);
	size = ft_strlen(end);
	str += ft_strlen(str) - 1;
	end += size - 1;
	while (size - 1)
	{
		if (*str != *end)
			return (0);
		str--;
		end--;
		size--;
	}
	return (1);
}
