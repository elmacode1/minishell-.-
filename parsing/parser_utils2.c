/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:35:07 by mael-gho          #+#    #+#             */
/*   Updated: 2025/08/15 19:04:58 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_argv(t_token **tokens, char **argv, t_cmd *new)
{
	int	i;

	i = 0;
	while (*tokens && !((*tokens)->type == PIPE && (*tokens)->state == GENERAL))
	{
		if ((*tokens)->type == WORD && !ft_strcmp((*tokens)->text, ""))
			*tokens = (*tokens)->next;
		else if ((*tokens)->type == WORD || (*tokens)->type == DQUOTE
			|| (*tokens)->type == SQUOTE)
			i += parse_word_group(tokens, argv + i);
		else if ((*tokens)->type == EMPTY_STR)
		{
			argv[i++] = ft_strdup2("");
			*tokens = (*tokens)->next;
		}
		else if (is_redirect_token(*tokens))
			parse_redirect(tokens, new);
		else
		{
			*tokens = (*tokens)->next;
		}
	}
	argv[i] = NULL;
	argv[i + 1] = NULL;
}

t_redirect	*create_redirect(char *filename, int type)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	free_helper(new);
	if (type == HEREDOC)
	{
		new->filename = NULL;
		new->delimiter = ft_strdup2(filename);
	}
	else
	{
		new->filename = ft_strdup2(filename);
		new->delimiter = NULL;
	}
	new->type = type;
	new->next = NULL;
	return (new);
}
