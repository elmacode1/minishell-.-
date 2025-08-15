/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extern_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:16 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 19:19:44 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_access(char **paths, char *cmd)
{
	char	*slash;
	char	*cmd_path;
	int		i;

	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		slash = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(slash, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(slash);
			return (cmd_path);
		}
		free(slash);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_shell *shell, char *cmd)
{
	char	*env;
	char	**paths;
	char	*result;

	result = NULL;
	env = get_env_var(shell, "PATH");
	if (!env)
		return (NULL);
	paths = ft_split(env, ':');
	result = path_access(paths, cmd);
	free_array(paths);
	return (result);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

int	check_access(t_cmd *cmd)
{
	if (access(cmd->argv[0], F_OK) != 0)
	{
		print_error("minishell: ", cmd->argv[0],
			": No such file or directory\n");
		return (127);
	}
	if (is_directory(cmd->argv[0]))
	{
		print_error("minishell: ", cmd->argv[0], ": Is a directory\n");
		return (126);
	}
	if (access(cmd->argv[0], X_OK) != 0)
	{
		print_error("minishell: ", cmd->argv[0], ": Permission denied\n");
		return (126);
	}
	return (0);
}

int	valid_cmd(t_shell *shell, t_cmd *cmd, char **path)
{
	int	status;

	if (cmd->argv[0][0] == '/' || (cmd->argv[0][0] == '.'
			&& cmd->argv[0][1] == '/'))
	{
		status = check_access(cmd);
		if (status != 0)
			return (status);
		*path = ft_strdup(cmd->argv[0]);
	}
	else
		*path = get_cmd_path(shell, cmd->argv[0]);
	if (!*path)
	{
		print_error("minishell: ", cmd->argv[0], ": command not found\n");
		return (127);
	}
	return (0);
}
