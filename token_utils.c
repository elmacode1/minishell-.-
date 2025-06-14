#include "minishell.h"

// int is_space(char c)
// {
//     return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
// }
// int is_special(char c)
// {
// 	if (c == '|' || c == '<' || c == '>'|| c == '\n'
// 		|| c == '\'' || c == '\"' || c == '$' || is_space(c))
// 		return (1);
// 	return (0);
// }

int count_word(char *s)
{
	int count;

	count = 0;
	while(!is_special(s[count]) && s[count])
		count++;
	return count;
}

t_token	*ft_lstnew(char *text, t_tokentype  type)
{
	t_token	*node;
	t_all *global;

	global = static_var();
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	

	node->text = text;
	node->type = type;
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