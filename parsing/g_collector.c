#include "../minishell.h"

t_all *static_var(){
	static t_all global;

	return(&global);
}

t_free *free_lst_new(void *content)
{
	t_free *node;
	node = malloc(sizeof(t_free));
	if(!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return (node);
}
t_free	*free_lstlast(t_free *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
	{
		node = node->next;
	}
	return (node);
}
void	free_lstadd_back(t_free **node, t_free *new)
{
	t_free	*tmp;

	if (node == NULL || new == NULL)
		return ;
	tmp = *node;
	if (tmp)
	{
		tmp = free_lstlast(tmp);
		tmp->next = new;
	}
	else
		*node = new;
}
void free_all(t_free *node){
	t_free *tmp;
	tmp = node;
	
	while (tmp)
	{
		tmp = tmp->next;
		if(!node->content)
		free(node->content);
		free(node);
		node = tmp;
	}
}

void free_helper(void *ptr)
{
	t_all *glob;

	glob = static_var();
	free_lstadd_back(&glob->free_list,free_lst_new(ptr));
}