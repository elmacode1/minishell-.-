/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:28 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 00:41:43 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->argv || !cmd->argv[0])
		return (handle_redirections(cmd));
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(shell, cmd));
	else
		return (execute_external(shell, cmd));
}

int	open_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_cmd		*temp;
	t_redirect	*current;

	temp = cmd;
	while (cmd)
	{
		current = cmd->redirections;
		while (current)
		{
			if (current->type == HEREDOC)
			{
				if (heredoc_handeler(current, &shell->exit_status) == 130)
				{
					shell->exit_status = 130;
					return (130);
				}
			}
			current = current->next;
		}
		cmd = cmd->next;
	}
	cmd = temp;
	return (0);
}

void	close_heredocs(t_cmd *cmd)
{
	t_cmd		*temp;
	t_redirect	*current;

	temp = cmd;
	while (cmd)
	{
		current = cmd->redirections;
		while (current)
		{
			if (current->type == HEREDOC && current->filename)
			{
				unlink(current->filename);
				free(current->filename);
				current->filename = NULL;
			}
			current = current->next;
		}
		cmd = cmd->next;
	}
	cmd = temp;
}

void	execute(t_shell *shell, t_cmd *cmd)
{
	if (cmd)
	{
		if (open_heredocs(cmd, shell) == 130)
			return ;
		if (cmd->argv[0])
		{
			if (cmd->next)
				shell->exit_status = execute_pipes(shell, cmd);
			else
				shell->exit_status = execute_cmd(shell, cmd);
		}
	}
}
