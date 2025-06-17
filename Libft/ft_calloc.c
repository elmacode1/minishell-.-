/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:52:46 by oukadir           #+#    #+#             */
/*   Updated: 2024/11/10 18:03:54 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	if (num_elements == 0 || element_size == 0)
		return (malloc(0));
	if (num_elements > SIZE_MAX / element_size)
		return (NULL);
	p = (unsigned char *)malloc(num_elements * element_size);
	if (p == NULL)
		return (NULL);
	while (i < num_elements * element_size)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
