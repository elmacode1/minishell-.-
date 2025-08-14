/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:51:56 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 01:19:08 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exetern_part(t_cmd *cmd, t_pipes *pipe, t_shell *shell, t_all *g)
{
	int	status;

	status = validate_arg(cmd, pipe->tmp, &pipe->path, shell);
	if (status != -1)
	{
		free_all(&g->free_list);
		exit(status);
	}
	execve(pipe->path, cmd->argv, shell->env_copy);
	free(pipe->path);
	ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
	free_all(&g->free_list);
	exit(126);
}

void	init_heredoc(t_heredoc *heredoc)
{
	static int	counter;

	free_helper(heredoc);
	heredoc->id = ft_itoa(counter++);
	heredoc->tempfile = ft_strjoin2("/tmp/tempfile", heredoc->id);
}
