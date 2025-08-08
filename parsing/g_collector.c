/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael-gho <mael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:40:05 by mael-gho          #+#    #+#             */
/*   Updated: 2025/08/08 22:05:45 by mael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_free	*free_lst_new(void *content)
{
	t_free	*new;

	if (!content)
		return (NULL);
	new = (t_free *)malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_free	*free_lstlast(t_free *node)
{
	if (!node)
		return (NULL);
	if (node->next == NULL)
		return (node);
	while (node->next)
		node = node->next;
	return (node);
}

void	free_lstadd_back(t_free **node, t_free *new)
{
		if (node != NULL && new != NULL)
	{
		if (*node == NULL)
		{
			*node = new;
			new->next = NULL;
		}
		else
		{
			free_lstlast(*node);
			free_lstlast(*node)->next = new;
		}
	}
}

void	free_all(t_free **node)
{
	t_free	*tmp;

	if (!node || !*node)
		return ;
	while (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		free(tmp->content);
		free(tmp);
	}
	*node = NULL;
}

void	free_helper(void *ptr)
{
    t_all	*glob;
    t_free	*new_node;

    if (!ptr)
        return ;
    glob = static_var();
    new_node = free_lst_new(ptr);
    if (!new_node)
    {
        free(ptr);
        return ;
    }
    free_lstadd_back(&glob->free_list, new_node);
}