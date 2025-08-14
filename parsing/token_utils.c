/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:20:15 by oukadir           #+#    #+#             */
/*   Updated: 2025/08/14 17:20:40 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(char *s)
{
	int	count;

	count = 0;
	while (!is_special(s[count]) && s[count])
		count++;
	return (count);
}

t_token	*ft_lstnew_token(char *text, t_state state, t_tokentype type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	free_helper(node);
	if (!node)
		return (NULL);
	node->text = text;
	node->type = type;
	node->state = state;
	node->next = NULL;
	return (node);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	tmp = *lst;
	if (tmp)
	{
		tmp = ft_lstlast_token(tmp);
		tmp->next = new;
	}
	else
		*lst = new;
}
