/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:46:36 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/22 22:25:10 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

/*
* The ft_itoa function converts an integer to a string.
*/
char	*ft_itoa(int n)
{
	char	*numbers;
	long	temp;
	int		n_digits;

	temp = n;
	n_digits = count_digit(n);
	numbers = malloc(sizeof(char) * (n_digits + 1));
	numbers[n_digits] = 0;
	if (temp < 0)
		temp = -temp;
	while (n_digits)
	{
		n_digits--;
		numbers[n_digits] = temp % 10 + '0';
		temp = temp / 10;
	}
	if (n < 0)
		numbers[0] = '-';
	return (numbers);
}
