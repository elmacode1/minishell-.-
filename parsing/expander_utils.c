/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:37:43 by mael-gho          #+#    #+#             */
/*   Updated: 2025/08/16 00:13:35 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	string_search(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
	{
		if (!str1[i + 1] && str2[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	get_env_index(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (string_search(str, env[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_strdup2(&str[i + 1]));
		i++;
	}
	return (NULL);
}

int	special_char(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '%' || str[i] == '+') || str[i] == ':' || str[i] == '/'
		|| str[i] == '.' || str[i] == '=')
		return (1);
	return (0);
}
