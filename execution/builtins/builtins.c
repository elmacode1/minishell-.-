/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:43:22 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/05 17:09:18 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_builtin(t_shell *shell)
{
	shell->builtinds[0] = (t_builtin){"echo", &ft_echo};
	shell->builtinds[1] = (t_builtin){"cd", &ft_cd};
	shell->builtinds[2] = (t_builtin){"pwd", &ft_pwd};
	shell->builtinds[3] = (t_builtin){"export", &ft_export};
	shell->builtinds[4] = (t_builtin){"unset", &ft_unset};
	shell->builtinds[5] = (t_builtin){"env", &ft_env};
	shell->builtinds[6] = (t_builtin){"exit", &ft_exit};
	shell->builtinds[7] = (t_builtin){NULL, NULL};
}
