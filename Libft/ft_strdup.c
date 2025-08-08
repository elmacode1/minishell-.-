/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:16:43 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/08 14:12:08 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*c;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	c = (char *)malloc((len + 1) * sizeof(char));
	free_helper(c);
	if (c == NULL)
		return (NULL);
	while (i < len)
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
