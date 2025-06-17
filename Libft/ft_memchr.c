/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:20:45 by oukadir           #+#    #+#             */
/*   Updated: 2024/11/09 16:21:27 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*st;
	size_t			i;

	i = 0;
	ch = (unsigned char)c;
	st = (unsigned char *)s;
	while (i < n)
	{
		if (st[i] == ch)
			return ((void *)(st + i));
		i++;
	}
	return (NULL);
}
