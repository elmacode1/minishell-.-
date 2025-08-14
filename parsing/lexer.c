/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:13:16 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 17:14:53 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_word(char *str, int *i, t_state state, t_token **head)
{
	ft_lstadd_back_token(head, ft_lstnew_token(ft_getword(str + *i), state,
			WORD));
	*i += count_word(str + *i) - 1;
}

t_token	*lexer(char *str)
{
	t_token	*head;
	t_state	state;
	int		i;

	head = NULL;
	state = GENERAL;
	i = 0;
	while (str[i])
	{
		if (is_special(str[i]))
			lexer_special(str, &i, &state, &head);
		else
			lexer_word(str, &i, state, &head);
		i++;
	}
	return (head);
}
