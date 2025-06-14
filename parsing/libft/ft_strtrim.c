/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:41:03 by mael-gho          #+#    #+#             */
/*   Updated: 2024/11/28 20:24:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (s1[start] && check(s1[start], set))
		start++;
	while ((end >= start) && check(s1[end], set))
		end--;
	str = malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
