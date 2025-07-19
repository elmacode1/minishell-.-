#include "../minishell.h"

int count_word(char *s)
{
	int count;

	count = 0;
	while(!is_special(s[count]) && s[count])
		count++;
	return count;
}

t_token	*ft_lstnew(char *text,t_state state, t_tokentype  type)
{
	t_token	*node;
	t_all *global;

	global = static_var();
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
t_token	*ft_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	tmp = *lst;
	if (tmp)
	{
		tmp = ft_lstlast(tmp);
		tmp->next = new;
	}
	else
		*lst = new;
}