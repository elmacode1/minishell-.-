/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:39:36 by mael-gho          #+#    #+#             */
/*   Updated: 2025/07/17 22:37:19 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	**ft_free(char **res, int j)
{
		
	while (j >= 0)
	{
		free (res[j]);
		j--;
	}
	free (res);
	return (NULL);
}

static char	**fill(const char *str, char c, char **res)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		start = i;
		while (str[i] != c && str[i])
			i++;
		res[j] = malloc(sizeof(char) * (i - start + 1));
		if (!res[j])
			return (ft_free(res, j - 1));
		ft_strlcpy(res[j], str + start, i - start + 1);
		j++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(const char *str, char c)
{
	char	**res;
	int		count;

	if (!str)
		return (NULL);
	count = word_count(str, c);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	if (count == 0)
	{
		res[0] = NULL;
		return (res);
	}
	return (fill(str, c, res));
}
