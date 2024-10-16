/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_starts_with.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 02:06:46 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/23 02:32:23 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Determines whether the given string starts with a specified substring. 
*/
#include "libft.h"

int	ft_str_starts_with(const char *str, const char *start)
{
	if (ft_strlen(str) < ft_strlen(start))
		return (0);
	while (*start)
	{
		if (*str != *start)
			return (0);
		start++;
		str++;
	}
	return (1);
}
