/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:54 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/06 15:42:16 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**create_pipes(int n_cmds)
{
	int	j;
	int	**pipes;

	j = 0;
	pipes = malloc(sizeof(int *) * (n_cmds - 1));
	if (!pipes)
		return (NULL);
	while (j < n_cmds - 1)
	{
		pipes[j] = malloc(sizeof(int) * 2);
		if (!pipes[j])
			return (NULL);
		if (pipe(pipes[j]) == -1)
		{
			perror("pipe failes\n");
			return (NULL);
		}
		j++;
	}
	return (pipes);
}

void	free_pipes(int **pipes, int n_cmds)
{
	int	j;

	j = 0;
	while (j < n_cmds - 1)
	{
		free(pipes[j]);
		j++;
	}
	free(pipes);
}

void	waiting_all(int n_cmds, t_shell *shell, int *pids)
{
	int	j;
	int	status;
	int	pid;

	j = 0;
	while (j < n_cmds)
	{
		pid = waitpid(pids[j], &status, 0);
		j++;
	}
	if (pid != -1)
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			else if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			shell->exit_status = 128 + WTERMSIG(status);
		}
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	builtin_exec_pipe(t_shell *shell, char **argv)
{
	int		i;
	char	*name;

	i = 0;
	name = argv[0];
	while (shell->builtinds[i].name)
	{
		if (strcmp(shell->builtinds[i].name, name) == 0)
			return (shell->builtinds[i].cmd_func(shell, argv));
		i++;
	}
	return (0);
}

int	count_cmds(t_cmd *cmd)
{
	int	n_cmds;

	n_cmds = 0;
	while (cmd)
	{
		n_cmds++;
		cmd = cmd->next;
	}
	return (n_cmds);
}
