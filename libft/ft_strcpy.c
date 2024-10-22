/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:24:30 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/22 18:28:25 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	char	*saved_dest;

	saved_dest = dest;
	while (src && *src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest++ = '\0';
	return (saved_dest);
}

