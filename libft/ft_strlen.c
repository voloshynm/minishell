/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:01:33 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:34:27 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strlen function calculates the length of the string pointed to by str.
*/
size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	while (*str++)
		x++;
	return (x);
}
