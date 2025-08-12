/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:33 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/06 14:39:27 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char *var)
{
	int	i;

	i = 0;
	if (!var || !(*var) || (!isalpha(*var) && *var != '_'))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_error(char *ms1, char *arg, char *ms2)
{
	ft_putstr_fd(ms1, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(ms2, STDERR_FILENO);
}

int	compose_varname(char **new_var, int len, char *name, char *var)
{
	*new_var = malloc(len);
	free_helper(*new_var);
	if (!new_var)
		return (-1);
	*new_var = ft_strjoin2(name, "=");
	*new_var = ft_strjoin2(*new_var, var);
	return (0);
}
