/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:40:03 by mael-gho          #+#    #+#             */
/*   Updated: 2024/11/29 23:24:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t    ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t    dest_len;
    size_t    total_len;
    size_t    i;

    dest_len = 0;
    i = 0;
    if (!dst && size == 0)
        return (0);
    while (dst[dest_len] && dest_len <= size)
    {
        dest_len++;
    }
    if (dest_len >= size)
        return (size + ft_strlen(src));
    total_len = dest_len + ft_strlen(src);
    while (src[i] && dest_len < size - 1)
        dst[dest_len++] = src[i++];
    dst[dest_len] = '\0';
    return (total_len);
}
