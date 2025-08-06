/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:47 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/05 13:43:48 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_shell *shell, char **argv)
{
	(void)shell;
	if (!argv[1])
		exit(shell->exit_status);
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit : too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (is_num(argv[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
		shell->exit_status = 2;
		exit(2);
	}
	shell->exit_status = atoi(argv[1]) % 256;
	exit(shell->exit_status);
}
