/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:30:50 by mael-gho          #+#    #+#             */
/*   Updated: 2025/08/08 23:08:00 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_exit_status(t_token *token, t_shell *shell)
{
	token->text = ft_strjoin2(ft_itoa(shell->exit_status), token->text + 2);
	token->type = WORD;
}

static void	expand_env_var(t_token *token, t_shell *shell)
{
	if (get_env_index(token->text + 1, shell->env_copy) >= 0)
		token->text = get_value(shell->env_copy
			[get_env_index(token->text + 1, shell->env_copy)]);
	else
		token->text = ft_strdup2("");
	token->type = WORD;
}

void	expander(t_token **head, t_shell *shell)
{
	t_token	*tmp_head;

	tmp_head = *head;
	while (tmp_head)
	{
		if ((tmp_head->type == ENV && !strncmp(tmp_head->text + 1, "", 1))
			|| special_char(tmp_head->text + 1))
			tmp_head->type = WORD;
		if (tmp_head->state != IN_SQUOTE && tmp_head->type == ENV
			&& !strncmp(tmp_head->text + 1, "?", 1))
			expand_exit_status(tmp_head, shell);
		else if (tmp_head->state != IN_SQUOTE && tmp_head->type == ENV)
			expand_env_var(tmp_head, shell);
		else if (tmp_head->state == IN_SQUOTE && tmp_head->type == ENV)
			tmp_head->type = WORD;
		tmp_head = tmp_head->next;
	}
}
