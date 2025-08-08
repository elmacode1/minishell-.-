/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:43 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/08 23:02:55 by mael-gho         ###   ########.fr       */
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
		free(tempfile);
		exit(1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
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
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		unlink(tempfile);
		free(tempfile);
		*exit_status = 130;
		return (130);
	}
	current->filename = strdup(tempfile);
	free(tempfile);
	return (0);
}

int	heredoc_handeler(t_redirect *current, int *exit_status)
{
	int			status;
	static int	counter;
	int			ret;
	t_heredoc	*heredoc;
	t_all *g;
	g = static_var();
	heredoc = malloc(sizeof(t_heredoc));
	heredoc->id = ft_itoa(counter++);
	heredoc->tempfile = ft_strjoin("/tmp/tempfile", heredoc->id);
	free(heredoc->id);
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
		free(heredoc);
		return (ret);
	}
}
