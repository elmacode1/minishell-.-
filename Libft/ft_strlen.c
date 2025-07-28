/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:37:34 by oukadir           #+#    #+#             */
/*   Updated: 2025/07/27 14:54:33 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	len;

	len = 0;
	if(!c)
	return 0;
	while (c[len])
	{
		len++;
	}
	return (len);
}
