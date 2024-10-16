/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_rm_front_chars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:32:54 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/23 01:37:25 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The ft_str_rm_front_chars function removes the first n characters from the
 * string str and returns a new string with the remaining characters.
 * Old string needs to be freed
 */
char	*ft_str_rm_front_chars(char *str, int n)
{
	int	i;

	if (!str || n <= 0)
		return (str);
	i = 0;
	while (str[i] && i < n)
		i++;
	if (i == 0)
		return (str);
	return (ft_substr(str + i, 0, ft_strlen(str + i)));
}
