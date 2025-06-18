/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:08:52 by mael-gho          #+#    #+#             */
/*   Updated: 2024/11/30 00:23:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	size_t			i;

	if (n == 0)
		return (dest);
	tmpdst = (unsigned char *)dest;
	tmpsrc = (unsigned char *)src;
	i = 0;
	if (tmpdst > tmpsrc)
	{
		while (n-- > 0)
			tmpdst[n] = tmpsrc[n];
	}
	else
	{
		while (i < n)
		{
			tmpdst[i] = tmpsrc[i];
			i++;
		}
	}
	return (dest);
}

