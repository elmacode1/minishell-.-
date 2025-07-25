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
void	add_redirection(t_cmd *cmd, char *filename, int type)
{
	t_redirect *new_redirect;
	t_redirect *last;
	new_redirect = malloc(sizeof(t_redirect));
	free_helper(new_redirect);
	if(type == HEREDOC)
	{
		new_redirect->filename =NULL;
		new_redirect->delimiter =ft_strdup(filename);
	}
	else
	{
		new_redirect->filename =ft_strdup(filename);
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
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*new;
	char	**argv;
	int i;

	cmd = NULL;
	new = NULL;
	argv = NULL;
	i = 0;
	while (tokens)
	{
		new = new_cmd();
		argv = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
		free_helper(argv);
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
			else if (tokens->type == RED_IN)
			{
				tokens = lst_skip_spaces(tokens->next);
            	if (tokens && tokens->type == WORD)
				{
               		add_redirection(new, tokens->text, RED_IN);
			   		tokens = tokens->next;
			   		continue;
				}
        	} 
			else if (tokens->type == RED_OUT)
			{
				tokens = lst_skip_spaces(tokens->next);
            	if (tokens && tokens->type == WORD)
				{
                	add_redirection(new, tokens->text, RED_OUT);
					tokens = tokens->next;
					continue;
           		}
        	}
			else if (tokens->type == APPEND)
			{
				tokens = lst_skip_spaces(tokens->next);
            	if (tokens && tokens->type == WORD)
				{
					add_redirection(new, tokens->text, APPEND);
					tokens = tokens->next;
					continue;
				}
        	}
			else if (tokens->type == HEREDOC)
			{
				tokens = lst_skip_spaces(tokens->next);
				if (tokens && tokens->type == WORD)
				{
					add_redirection(new, tokens->text, HEREDOC);
					tokens = tokens->next;
					continue;
				}
			}
			tokens = tokens->next;		
		}
		argv[i]=NULL;
		i = 0;
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