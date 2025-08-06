/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:28 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/05 17:54:53 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*check_first_arg(char *arg, t_shell *shell)
{
	char	*path;

	if (!arg || ft_strcmp(arg, "~") == 0)
	{
		path = get_env_var(shell, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (path);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		path = get_env_var(shell, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
		return (path);
	}
	return (arg);
}

int	chdir_error(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *shell, char **argv)
{
	char	cwd[1024];
	char	*path;

	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	path = check_first_arg(argv[1], shell);
	if (!path)
		return (1);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("minishell: cd: error retreiving current directory\n",
			STDERR_FILENO);
		return (1);
	}
	if (chdir_error(path))
		return (1);
	set_env_var(shell, "OLDPWD", cwd);
	if (!getcwd(cwd, sizeof(cwd)))
		ft_putstr_fd("minishell: cd: could not update PWD\n", STDERR_FILENO);
	else
		set_env_var(shell, "PWD", cwd);
	return (0);
}
