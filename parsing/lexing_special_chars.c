/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_special_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:15:40 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 01:15:29 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe_and_space(char *str, int i, t_state state, t_token **head)
{
	if (str[i] == '|')
		ft_lstadd_back_token(head, ft_lstnew_token("|", state, PIPE));
	else if (is_space(str[i]))
		ft_lstadd_back_token(head, ft_lstnew_token(" ", state, WHITESPACE));
}

void	lexing_redirections(char *str, int *i, t_state state, t_token **head)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		ft_lstadd_back_token(head, ft_lstnew_token(">>", state, APPEND));
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		ft_lstadd_back_token(head, ft_lstnew_token("<<", state, HEREDOC));
		(*i)++;
	}
	else if (str[*i] == '>')
		ft_lstadd_back_token(head, ft_lstnew_token(">", state, RED_OUT));
	else if (str[*i] == '<')
		ft_lstadd_back_token(head, ft_lstnew_token("<", state, RED_IN));
}

void	lexing_env_variable(char *str, int *i, t_state state, t_token **head)
{
	ft_lstadd_back_token(head, ft_lstnew_token(get_env(str + *i), state, ENV));
	(*i)++;
	*i += count_word(str + *i) - 1;
}

void	lexer_special(char *str, int *i, t_state *state, t_token **head)
{
	if (str[*i] == '|' || is_space(str[*i]))
		handle_pipe_and_space(str, *i, *state, head);
	else if (str[*i] == '\'' || str[*i] == '\"')
	{
		quotes_handler(&str[*i], state, head);
		if (ft_lstlast_token(*head)->type == EMPTY_STR)
			(*i)++;
	}
	else if (str[*i] == '>' || str[*i] == '<')
		lexing_redirections(str, i, *state, head);
	else if (str[*i] == '\n')
		ft_lstadd_back_token(head, ft_lstnew_token("\n", *state, NEW_LINE));
	else if (str[*i] == '$')
		lexing_env_variable(str, i, *state, head);
}
