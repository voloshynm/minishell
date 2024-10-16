/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:21:15 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/23 01:46:35 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Reverses the given string and returns a new dynamically allocated string
 * containing the reversed content.
 */
char	*ft_strrev(char *str)
{
	char	*new_str;
	int		size;
	int		i;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	new_str = malloc(sizeof(char) * size + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (size)
	{
		new_str[i] = str[size - 1];
		i++;
		size--;
	}
	new_str[i] = 0;
	return (new_str);
}
