/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:55:23 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:29:32 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* The ft_putchar_fd function writes the character c to the file descriptor fd.
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
