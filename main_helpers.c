/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:23:40 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 01:08:16 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_input(t_shell *shell)
{
	char	*input;
	t_token	*head;
	t_cmd	*cmd;
	t_all	*global;

	global = static_var();
	input = readline("minishell$ ");
	if (!input)
	{
		printf("exit\n");
		free_all(&global->free_list);
		exit(1);
	}
	if (*input)
	{
		add_history(input);
		head = lexer(input);
		cmd = parsing(head, shell);
		if (cmd)
			execute(shell, cmd);
	}
	shell->lines++;
	free(input);
}

t_cmd	*parsing(t_token *head, t_shell *shell)
{
	t_cmd	*cmd;

	if (!check_errors(head))
		return (NULL);
	expander(&head, shell);
	cmd = parse_tokens(head);
	return (cmd);
}
