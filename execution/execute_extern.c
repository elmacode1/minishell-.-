/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:21 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 20:05:54 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	restore_tmp(int tmp_in, int tmp_out, int stat)
{
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_out);
	close(tmp_in);
	return (stat);
}

int	handle_parent_sig(int pid, int tmp_in, int tmp_out)
{
	int	status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_out);
	close(tmp_in);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		return (131);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		return (130);
	}
	return (WEXITSTATUS(status));
}

int	validate_arg(t_cmd *cmd, t_tmp *tmp, char **path, t_shell *shell)
{
	if (ft_strcmp(cmd->argv[0], "") == 0)
	{
		print_error("minishell: ", cmd->argv[0], ": command not found\n");
		return (127);
	}
	shell->exit_status = handle_redirections(cmd);
	if (shell->exit_status != 0)
	{
		dup2(tmp->tmp_in, STDIN_FILENO);
		dup2(tmp->tmp_out, STDOUT_FILENO);
		close(tmp->tmp_out);
		close(tmp->tmp_in);
		return (shell->exit_status);
	}
	shell->exit_status = valid_cmd(shell, cmd, path);
	if (shell->exit_status != 0)
	{
		dup2(tmp->tmp_in, STDIN_FILENO);
		dup2(tmp->tmp_out, STDOUT_FILENO);
		close(tmp->tmp_out);
		close(tmp->tmp_in);
		return (shell->exit_status);
	}
	return (-1);
}

void	handle_child(t_cmd *cmd, t_shell *shell, char *path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->argv, shell->env_copy);
	ft_putstr_fd("minishell: execve\n", STDERR_FILENO);
}

int	execute_external(t_shell *shell, t_cmd *cmd)
{
	int		pid;
	char	*path;
	int		ret;
	t_tmp	*tmp;

	tmp = malloc(sizeof(t_tmp));
	free_helper(tmp);
	tmp->tmp_out = dup(STDOUT_FILENO);
	tmp->tmp_in = dup(STDIN_FILENO);
	path = NULL;
	ret = validate_arg(cmd, tmp, &path, shell);
	if (ret != -1)
		return (ret);
	pid = fork();
	if (pid == 0)
	{
		handle_child(cmd, shell, path);
		exit(126);
	}
	else
	{
		ret = handle_parent_sig(pid, tmp->tmp_in, tmp->tmp_out);
		free(path);
		return (ret);
	}
}
