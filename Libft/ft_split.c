/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:42:06 by oukadir           #+#    #+#             */
/*   Updated: 2024/11/13 04:05:33 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 1;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			word++;
		i++;
	}
	return (word);
}

static char	*alloc_dup(char const *s, size_t len)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**free_strings(char **strings, size_t j)
{
	while (j > 0)
	{
		j--;
		free(strings[j]);
	}
	free(strings);
	return (NULL);
}

static char	**fill_strings(char **strings, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (start < i)
		{
			strings[j] = alloc_dup(s + start, i - start);
			if (strings[j] == NULL)
				return (free_strings(strings, j));
			j++;
		}
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**strings;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	strings = malloc(sizeof(char *) * (words + 1));
	if (!strings)
		return (NULL);
	strings = fill_strings(strings, s, c);
	return (strings);
}
