/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:35:19 by oukadir           #+#    #+#             */
/*   Updated: 2024/11/10 17:46:17 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		n;
	int		sign;

	i = 0;
	res = 0;
	n = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i++] == '-')
		sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = str[i] - 48;
		res = res * 10 + n;
		i++;
	}
	return (sign * res);
}
