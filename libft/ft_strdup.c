/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:12:30 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/30 22:41:47 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_strdup function allocates sufficient memory for a copy of the 
* string s1, and returns a pointer to the allocated memory.
*/
char	*ft_strdup(const char *s)
{
	int		length;
	char	*t_s;
	char	*new_str;
	char	*start;

	if (!s || *s == 0)
		return (NULL);
	t_s = (char *) s;
	length = ft_strlen(t_s);
	new_str = malloc((length + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*t_s)
	{
		*new_str = *t_s;
		new_str++;
		t_s++;
	}
	*new_str = 0;
	return (start);
}
