/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:39:02 by mael-gho          #+#    #+#             */
/*   Updated: 2024/11/29 21:25:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*st;
	unsigned char	ch;
	size_t			x;

	st = (unsigned char *)s;
	ch = (unsigned char)c;
	x = 0;
	while (x < n)
	{
		if (st[x] == ch)
			return ((void *)(st + x));
		x++;
	}
	return (NULL);
}
