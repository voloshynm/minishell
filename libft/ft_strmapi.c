/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:57:40 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:34:58 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strmapi function applies the function f to each character of 
* the string s, to create a new string. 
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	char			*result;
	char			*str;
	unsigned int	size;

	if (!s || !f)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	result = str;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (result);
}
