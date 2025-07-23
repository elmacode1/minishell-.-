#include "../minishell.h"
int	count_tokens(t_token *tokens)
{
	int count;

	count =0;			//echo "malak | taha" | test
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
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*new;
	char	**argv;
	int i;

	cmd = NULL;
	new = NULL;				//echo malak > c | test
	argv = NULL;
	i = 0;
	while (tokens)
	{
		argv = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
		while(tokens)
		{
			if(tokens->type == PIPE && tokens->state == GENERAL)
			break;
			if(!((tokens->type == WHITESPACE || tokens->type == DQUOTE || tokens->type == SQUOTE 
				|| tokens->type == RED_IN || tokens->type == RED_OUT|| tokens->type == APPEND
				|| tokens->type == HEREDOC) && tokens->state == GENERAL))
				{
					argv[i]=ft_strdup(tokens->text);
					i++;
				}
			tokens = tokens->next;		
		}
		argv[i]=NULL;
		i = 0;
		new = new_cmd();
		new->argv=argv;
		ft_lstadd_back_cmd(&cmd,new);
		if(tokens && tokens->type == PIPE )
		{
			tokens = tokens->next;
			new = NULL;
			argv = NULL;
		}  
	}
	return cmd;
}