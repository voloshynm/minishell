/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:37:55 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:38:35 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (*p1 != '\0' || *p2 != '\0')
	{
		if (*p1 > *p2)
			return (1);
		else if (*p1 < *p2)
			return (-1);
		p1++;
		p2++;
	}
	return (0);
}
