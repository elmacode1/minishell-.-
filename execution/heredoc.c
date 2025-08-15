/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:43 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/16 00:27:08 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_line(char *line, t_redirect *current)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document", STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(current->delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		return (1);
	}
	else if (strcmp(line, current->delimiter) == 0)
		return (1);
	return (0);
}

void	read_heredoc(t_shell *shell, t_redirect *current, int fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_child_sig);
		line = readline("> ");
		if (!ft_strncmp(line, "$", 1))
		{
			if (get_env_index(line + 1, shell->env_copy) >= 0)
				line = get_value(shell->env_copy[get_env_index(line + 1,
							shell->env_copy)]);
			else
				line = ft_strdup2("");
			if (valid_line(line, current) == 1)
				break ;
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			continue ;
		}
		if (valid_line(line, current) == 1)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc_child(t_shell *shell, t_redirect *current,
		char *tempfile)
{
	int	fd;

	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: heredoc\n", STDERR_FILENO);
		exit(1);
	}
	signal(SIGINT, handle_child_sig);
	signal(SIGQUIT, SIG_IGN);
	read_heredoc(shell, current, fd);
	close(fd);
}

int	check_sig(int status, char *tempfile, int *exit_status, t_redirect *current)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		unlink(tempfile);
		*exit_status = 130;
		return (130);
	}
	current->filename = ft_strdup2(tempfile);
	return (0);
}

int	heredoc_handeler(t_redirect *current, int *exit_status)
{
	int			status;
	int			ret;
	t_heredoc	*heredoc;
	t_all		*g;

	g = static_var();
	heredoc = malloc(sizeof(t_heredoc));
	init_heredoc(heredoc);
	signal(SIGINT, SIG_IGN);
	heredoc->pid = fork();
	if (heredoc->pid == 0)
	{
		handle_heredoc_child(g->shell, current, heredoc->tempfile);
		free_all(&g->free_list);
		exit(0);
	}
	else
	{
		waitpid(heredoc->pid, &status, 0);
		signal(SIGINT, handle_sigint);
		ret = check_sig(status, heredoc->tempfile, exit_status, current);
		return (ret);
	}
}
