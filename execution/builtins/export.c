/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:53 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/05 17:44:04 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_and_print(char **env)
{
	int		len;
	char	**sorted;

	len = 0;
	while (env[len])
		len++;
	sorted = copy_env(env);
	bubble_sort(sorted, len);
	print_env(sorted);
	free_env(sorted);
}

char	*get_var(t_shell *shell, char *name)
{
	int	len;
	int	i;

	i = 0;
	len = strlen(name);
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], name, len) == 0)
			return (&shell->env_copy[i][len + 1]);
		i++;
	}
	return (NULL);
}

void	update_env(t_shell *shell, char *equal, char *arg)
{
	char	*value;

	if (equal)
	{
		*equal = '\0';
		set_env_var(shell, arg, equal + 1);
		*equal = '=';
	}
	else
	{
		value = get_var(shell, arg);
		if (!value)
			add_new_var(shell, arg);
	}
}

int	ft_export(t_shell *shell, char **argv)
{
	int		i;
	char	*equal;
	int		ret;

	i = 1;
	ret = 0;
	if (!argv[1])
		sort_and_print(shell->env_copy);
	while (argv[i])
	{
		if (!is_valid(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret = 1;
			i++;
			continue ;
		}
		equal = ft_strchr(argv[i], '=');
		update_env(shell, equal, argv[i]);
		i++;
	}
	return (ret);
}
