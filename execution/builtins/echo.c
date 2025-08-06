/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:36 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/05 17:43:56 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_new_line(char **argv)
{
	int		i;
	char	*p;

	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		p = argv[i] + 2;
		while (*p == 'n')
			p++;
		if (*p != '\0')
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_shell *shell, char **argv)
{
	int	i;

	(void)shell;
	i = 1;
	i = check_new_line(argv);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (check_new_line(argv) == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
