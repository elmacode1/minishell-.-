/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:23:30 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/08 23:07:01 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, total_len);
	return (result);
}
char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup2(s2));
	if (!s2)
		return (ft_strdup2(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	free_helper(result);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, total_len);
	return (result);
}