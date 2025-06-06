/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:01:33 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/22 18:31:30 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strlen function calculates the length of the string pointed to by str.
*/
size_t	ft_strlen(const char *str)
{
	int	x;

	if (str == NULL)
		return (0);
	x = 0;
	while (*str++)
		x++;
	return (x);
}
