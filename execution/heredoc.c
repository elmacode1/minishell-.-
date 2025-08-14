/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:43 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 01:12:19 by oukadir          ###   ########.fr       */
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
	{
		free(line);
		return (1);
	}
	return (0);
}

void	handle_heredoc_child(t_redirect *current, char *tempfile)
{
	int		fd;
	char	*line;

	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: heredoc\n", STDERR_FILENO);
		exit(1);
	}
	signal(SIGINT, handle_child_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_child_sig);
		line = readline("> ");
		if (valid_line(line, current) == 1)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
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
		handle_heredoc_child(current, heredoc->tempfile);
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
