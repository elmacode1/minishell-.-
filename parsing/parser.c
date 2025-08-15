/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:18:13 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/15 19:04:42 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_token_text(char **tmp, t_token **tokens)
{
	*tmp = ft_strjoin2(*tmp, (*tokens)->text);
	(*tokens) = (*tokens)->next;
}

void	parse_inside_quotes(char **tmp, t_token **tokens, t_tokentype quote)
{
	while (*tokens && !((*tokens)->type == quote
			&& (*tokens)->state == GENERAL))
		append_token_text(tmp, tokens);
	if (*tokens && (*tokens)->type == quote && (*tokens)->state == GENERAL)
		(*tokens) = (*tokens)->next;
}

void	parse_next_word(char **tmp, t_token **tokens)
{
	t_tokentype	quote;

	if (((*tokens)->type == DQUOTE || (*tokens)->type == SQUOTE)
		&& (*tokens)->state == GENERAL)
	{
		quote = (*tokens)->type;
		(*tokens) = (*tokens)->next;
		parse_inside_quotes(tmp, tokens, quote);
	}
	else
		append_token_text(tmp, tokens);
}

int	parse_word_group(t_token **tokens, char **argv)
{
	char	*tmp;
	int		count;

	tmp = NULL;
	count = 0;
	while (*tokens && !(((*tokens)->type == WHITESPACE
				|| (*tokens)->type == RED_IN || (*tokens)->type == RED_OUT
				|| (*tokens)->type == APPEND || (*tokens)->type == HEREDOC)
			&& (*tokens)->state == GENERAL))
		parse_next_word(&tmp, tokens);
	if (tmp)
	{
		*argv = ft_strdup2(tmp);
		count++;
	}
	return (count);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*new;
	int		max_args;
	char	**argv;

	cmd = NULL;
	while (tokens)
	{
		new = new_cmd();
		max_args = count_tokens(tokens);
		argv = malloc(sizeof(char *) * (max_args + 2));
		if (!argv)
			return (NULL);
		free_helper(argv);
		fill_argv(&tokens, argv, new);
		new->argv = argv;
		ft_lstadd_back_cmd(&cmd, new);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmd);
}
