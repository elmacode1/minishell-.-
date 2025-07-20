/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:21:13 by oukadir           #+#    #+#             */
/*   Updated: 2024/11/08 17:53:11 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	value = (unsigned char)c;
	while (i < len)
	{
		ptr[i] = value;
		i++;
	}
	return (ptr);
}
