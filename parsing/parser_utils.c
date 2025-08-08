#include "../minishell.h"

int	count_tokens(t_token *tokens)
{
	int count;

	count =0;
	while(tokens)
	{
		if(tokens->type == PIPE && tokens->state == GENERAL)
			break;
		if(!((tokens->type == WHITESPACE || tokens->type == DQUOTE || tokens->type == SQUOTE 
			|| tokens->type == RED_IN || tokens->type == RED_OUT|| tokens->type == APPEND
			|| tokens->type == HEREDOC) && tokens->state == GENERAL))
			count++;
		tokens = tokens->next;		
	}
	return count;
}
t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	tmp = *lst;
	if (tmp)
	{
		tmp = ft_lstlast_cmd(tmp);
		tmp->next = new;
	}
	else
		*lst = new;
}
t_cmd	*new_cmd()
{
    t_cmd *new;
	
	new = malloc(sizeof(t_cmd));
	free_helper(new);
    if (!new)
		return NULL;
    new->argv = NULL;
	new->redirections = NULL;
    new->next = NULL;
    return new;
}
void	add_redirection(t_cmd *cmd, char *filename, int type)
{
	t_redirect *new_redirect;
	t_redirect *last;
	new_redirect = malloc(sizeof(t_redirect));
	free_helper(new_redirect);
	if(type == HEREDOC)
	{
		new_redirect->filename =NULL;
		new_redirect->delimiter =ft_strdup2(filename);
	}
	else
	{
		new_redirect->filename =ft_strdup2(filename);
		new_redirect->delimiter =NULL;
	}
	new_redirect->type = type;
	new_redirect->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redirect;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redirect;
	}
}