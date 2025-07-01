#include "minishell.h"


// t_all *static_var(){
// 	static t_all global;

// 	return(&global);
// }

t_free *lst_new_free(void *content)
{
	t_free *node;
	node = malloc(sizeof(t_free));
	if(!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return (node);
}
t_free	*lst_last(t_free *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
	{
		node = node->next;
	}
	return (node);
}
void	lstadd_back(t_free **node, t_free *new)
{
	t_free	*tmp;

	if (node == NULL || new == NULL)
		return ;
	tmp = *node;
	if (tmp)
	{
		tmp = ft_lstlast(tmp);
		tmp->next = new;
	}
	else
		*node = new;
}