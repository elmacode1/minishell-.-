/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:16:59 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 17:34:39 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	len;

	ch = (char)c;
	len = ft_strlen(s);
	if (ch == '\0')
		return ((char *)(s + len));
	while (len > 0)
	{
		len--;
		if (s[len] == ch)
			return ((char *)(s + len));
	}
	return (NULL);
}
