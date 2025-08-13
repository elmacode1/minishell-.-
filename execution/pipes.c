/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:02 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/13 22:02:55 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes(int n_cmds, int **pipes)
{
	int	j;

	j = 0;
	while (j < n_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	manage_pipes(int i, int **pipes, int n_cmds)
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < n_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	while (j < n_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	manage_cmd(t_cmd *cmd, t_shell *shell, t_pipes *pipe)
{
	int	status;
	t_all *g;

	g = static_var();
	if (!cmd->argv || !cmd->argv[0])
	{
		shell->exit_status = handle_redirections(shell, cmd);
		free_all(&g->free_list);
		exit(shell->exit_status);
	}
	else
	{
		if (is_builtin(cmd->argv[0]))
		{
			shell->exit_status = execute_builtin(shell, cmd);
			free_all(&g->free_list);
			exit(shell->exit_status);
		}
		else
		{
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
	}
}

void	init_vars(t_cmd *cmd, t_pipes *pipe)
{
	pipe->i = 0;
	pipe->tmp = malloc(sizeof(t_tmp));
	free_helper(pipe->tmp);
	pipe->tmp->tmp_out = dup(STDOUT_FILENO);
	pipe->tmp->tmp_in = dup(STDIN_FILENO);
	pipe->path = NULL;
	pipe->n_cmds = count_cmds(cmd);
	pipe->pipes = create_pipes(pipe->n_cmds);
	pipe->pids = malloc(sizeof(int) * pipe->n_cmds);
	free_helper(pipe->pids);
}

int	execute_pipes(t_shell *shell, t_cmd *cmd)
{
	t_pipes	*pipe;

	pipe = malloc(sizeof(t_pipes));
	free_helper(pipe);
	init_vars(cmd, pipe);
	while (pipe->i < pipe->n_cmds)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pipe->pid = fork();
		if (pipe->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			manage_pipes(pipe->i, pipe->pipes, pipe->n_cmds);
			manage_cmd(cmd, shell, pipe);
		}
		cmd = cmd->next;
		pipe->pids[pipe->i] = pipe->pid;
		pipe->i++;
	}
	close_pipes(pipe->n_cmds, pipe->pipes);
	waiting_all(pipe->n_cmds, shell, pipe->pids);
	// free_pipes(pipe->pipes, pipe->n_cmds);
	return (shell->exit_status);
}
