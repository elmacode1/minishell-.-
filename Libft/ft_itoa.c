/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 05:07:46 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/08 22:57:53 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../minishell.h"

static char	*convert_to_string(int n, int len)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	while (n > 0)
	{
		s[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (s);
}

static char	*handle_special_cases(int n)
{
	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	return (NULL);
}

static int	calculate_len(int n)
{
	int	num;
	int	len;

	len = 0;
	num = n;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*s;
	char	*special_case;
	int		sign;

	len = 0;
	sign = 0;
	special_case = handle_special_cases(n);
	if (special_case != NULL)
		return (special_case);
	len = calculate_len(n);
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	s = convert_to_string(n, len);
	if (s == NULL)
		return (NULL);
	if (sign == -1)
		s[0] = '-';
	return (s);
}
