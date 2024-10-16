/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:29:46 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/15 22:32:46 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strjoin function allocates (with malloc()) and returns a new string 
* which is the result of concatenating the string s1 with the string s2.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*t_s1;
	char	*t_s2;
	char	*new_str;
	char	*start;

	t_s1 = (char *)s1;
	t_s2 = (char *)s2;
	new_str = malloc(sizeof(char) * (ft_strlen(t_s1) + ft_strlen(t_s2)) + 1);
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*t_s1)
		*new_str++ = *t_s1++;
	while (*t_s2)
		*new_str++ = *t_s2++;
	*new_str = 0;
	return (start);
}
