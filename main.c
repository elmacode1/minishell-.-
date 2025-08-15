/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:23:23 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 22:59:15 by mael-gho         ###   ########.fr       */
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
	init_signals(&shell);
	while (1)
	{
		get_input(&shell);
	}
	return (0);
}
