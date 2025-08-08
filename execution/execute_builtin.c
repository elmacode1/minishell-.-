/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:09 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/07 17:03:43 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	int		i;
	char	**builtins;

	builtins = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit",
		NULL};
	i = 0;
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	builtin_func(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*name;

	i = 0;
	name = cmd->argv[0];
	while (shell->builtinds[i].name)
	{
		if (strcmp(shell->builtinds[i].name, name) == 0)
			return (shell->builtinds[i].cmd_func(shell, cmd->argv));
		i++;
	}
	return (0);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	int	tmp_out;
	int	tmp_in;
	int	status;

	tmp_out = dup(STDOUT_FILENO);
	tmp_in = dup(STDIN_FILENO);
	status = handle_redirections(shell, cmd);
	if (status != 0)
	{
		dup2(tmp_out, STDOUT_FILENO);
		dup2(tmp_in, STDIN_FILENO);
		close(tmp_in);
		close(tmp_out);
		return (status);
	}
	status = builtin_func(shell, cmd);
	dup2(tmp_out, STDOUT_FILENO);
	dup2(tmp_in, STDIN_FILENO);
	close(tmp_in);
	close(tmp_out);
	return (status);
}

int	check_access_redir(t_redirect *current)
{
	if (access(current->filename, F_OK) != 0)
	{
		print_error("minishell: ", current->filename,
			": No such file or directory\n");
		return (1);
	}
	if (access(current->filename, X_OK) != 0)
	{
		print_error("minishell: ", current->filename, ": Permission denied\n");
		return (126);
	}
	return (1);
}
