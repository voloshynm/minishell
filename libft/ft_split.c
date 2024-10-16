/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:58:38 by sandre-a          #+#    #+#             */
/*   Updated: 2024/10/04 16:01:10 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char sep)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != sep && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == sep)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*get_next_word(const char **str, char sep)
{
	const char	*start;
	size_t		len;

	while (**str == sep)
		(*str)++;
	start = *str;
	while (**str && **str != sep)
		(*str)++;
	len = *str - start;
	return (ft_substr(start, 0, len));
}

/*
 * The ft_split function splits a string into words,
 * and returns an array of strings.
 */
char	**ft_split(char const *str, char sep)
{
	char	**strings;
	int		word_count;
	int		i;

	if (!str)
		return (NULL);
	word_count = count_words(str, sep);
	strings = malloc(sizeof(char *) * (word_count + 1));
	if (!strings)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		strings[i] = get_next_word(&str, sep);
		i++;
	}
	strings[i] = NULL;
	return (strings);
}

/*
 * The free_ft_split function frees the memory allocated for an array strings.
 */
void	free_ft_split(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
