/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:08 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 18:03:39 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input(t_redirect *current, int *fd_in)
{
	int	ret;

	if (current->type == HEREDOC || current->type == RED_IN)
	{
		if (ft_strcmp(current->filename, "/dev/stdin") == 0)
		{
			current = current->next;
			return (0);
		}
		if (*fd_in != -1)
			close(*fd_in);
		*fd_in = open(current->filename, O_RDONLY);
		if (*fd_in < 0)
		{
			ret = check_access_redir(current);
			return (ret);
		}
	}
	return (0);
}

int	handle_output(t_redirect *current, int *fd_out)
{
	int	flags;

	if (current->type == RED_OUT || current->type == APPEND)
	{
		if (ft_strcmp(current->filename, "/dev/stdout") == 0)
		{
			current = current->next;
			return (0);
		}
		if (*fd_out != -1)
			close(*fd_out);
		if (current->type == RED_OUT)
			flags = O_CREAT | O_WRONLY | O_TRUNC;
		else
			flags = O_CREAT | O_WRONLY | O_APPEND;
		*fd_out = open(current->filename, flags, 0644);
		if (*fd_out < 0)
		{
			if (access(current->filename, X_OK) != 0)
				print_error("minishell: ", current->filename,
					": Permission denied\n");
			return (1);
		}
	}
	return (0);
}

void	restore_fds(int *fd_in, int *fd_out, int *tmp_in, int *tmp_out)
{
	if (*fd_in != -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (*fd_out != -1)
	{
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
	if (*tmp_out != -1)
	{
		dup2(*tmp_out, STDOUT_FILENO);
		close(*tmp_out);
	}
	if (*tmp_in != -1)
	{
		dup2(*tmp_in, STDIN_FILENO);
		close(*tmp_in);
	}
}

int	check_current(t_redirect *current, int *fd_in, int *fd_out)
{
	int	status;

	while (current)
	{
		status = handle_input(current, fd_in);
		if (status != 0)
			return (status);
		status = handle_output(current, fd_out);
		if (status != 0)
			return (status);
		current = current->next;
	}
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	int			fd_in;
	int			fd_out;
	t_tmp		*tmp;
	t_redirect	*current;
	int			status;

	tmp = malloc(sizeof(t_tmp));
	free_helper(tmp);
	current = cmd->redirections;
	fd_in = -1;
	fd_out = -1;
	tmp->tmp_in = -1;
	tmp->tmp_out = -1;
	if (!current)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
	{
		tmp->tmp_out = dup(STDOUT_FILENO);
		tmp->tmp_in = dup(STDIN_FILENO);
	}
	status = check_current(current, &fd_in, &fd_out);
	if (status != 0)
		return (status);
	restore_fds(&fd_in, &fd_out, &tmp->tmp_in, &tmp->tmp_out);
	return (0);
}
