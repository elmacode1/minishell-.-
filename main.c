/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:23:23 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 17:23:31 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env_copy = copy_env(envp);
	shell.lines = 0;
	shell.exit_status = 0;
	init_builtin(&shell);
	init_signals();
	while (1)
	{
		get_input(&shell);
	}
	return (0);
}
