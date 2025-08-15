/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:15 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 22:57:32 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_sig(int sig)
{
	t_all	*g;

	(void)sig;
	g = static_var();
	free_all(&g->free_list);
	exit(130);
}

void	handle_sigint(int sig)
{
	t_all	*g;

	(void)sig;
	g = static_var();
	g->shell->exit_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	exit(131);
}

void	init_signals(t_shell *shell)
{
	t_all	*g;

	g = static_var();
	g->shell = shell;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
