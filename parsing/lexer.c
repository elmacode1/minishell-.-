#include "../minishell.h"

char *ft_getword(char *s)
{
	int c;
	char *str;

	c = count_word(s);
	str = malloc(sizeof(char)*(c+1));
	free_helper(str);
	ft_strlcpy(str,s,c+1);
	return str;
}
char *get_env(char *s)
{
	int c;
	char *str;
	
	c = count_word(s+1);
	str = malloc(sizeof(char)*(c+2));
	free_helper(str);
	ft_strlcpy(str,s,c+2);
	return str;
}

void quotes_hander(char c, t_state *state, t_token **head)
{
	if(c == '\"'){

		
		if(*state ==IN_DQUOTE)
		{
			*state = GENERAL;
			ft_lstadd_back_token(head,ft_lstnew_token("\"", *state, DQUOTE));
		}
		else if (*state == GENERAL)
		{
			ft_lstadd_back_token(head,ft_lstnew_token("\"", *state, DQUOTE));
			*state = IN_DQUOTE;
		}
		else
		{
			ft_lstadd_back_token(head,ft_lstnew_token("\"", *state, DQUOTE));
		}
	}
	else if(c == '\''){
		if(*state ==IN_SQUOTE)
		{
			*state = GENERAL;
			ft_lstadd_back_token(head,ft_lstnew_token("\'", *state, SQUOTE));
		}
		else if (*state == GENERAL)
		{
			ft_lstadd_back_token(head,ft_lstnew_token("\'", *state, SQUOTE));
			*state = IN_SQUOTE;
		}
		else
		{
			ft_lstadd_back_token(head,ft_lstnew_token("\'", *state, SQUOTE));
		}
	}
}

t_token *lexer(char *str)
{
	t_token *head;
	// t_all *global;
	t_state state;
	int i;

	state = GENERAL;
	head = NULL;
	i = 0;
	while(str[i])
	{	
		if(is_special(str[i]))
		{
			if(str[i]=='|')
				ft_lstadd_back_token(&head,ft_lstnew_token("|",state ,PIPE));
			else if(is_space(str[i])){
				ft_lstadd_back_token(&head,ft_lstnew_token(" ",state ,WHITESPACE));
			}
			else if(str[i] == '\'' || str[i] == '\"')
				quotes_hander(str[i], &state, &head);

			else if(str[i] == '>' && str[i+1] == '>')
			{
				ft_lstadd_back_token(&head,ft_lstnew_token(">>",state, APPEND));
				i++;
			}
			else if(str[i] == '<' && str[i+1] == '<')
			{
				ft_lstadd_back_token(&head,ft_lstnew_token("<<",state, HEREDOC));
				i++;
			}
			else if(str[i] == '>')
				ft_lstadd_back_token(&head,ft_lstnew_token(">",state ,RED_OUT));
			else if(str[i] == '<')
				ft_lstadd_back_token(&head,ft_lstnew_token("<",state ,RED_IN));
			else if(str[i] == '\n')
				ft_lstadd_back_token(&head,ft_lstnew_token("\n",state, NEW_LINE));
			else if(str[i] == '$'){
				
					ft_lstadd_back_token(&head,ft_lstnew_token(get_env(str+i),state, ENV));
					i++;
					i+=count_word(str+i)-1;
				
			}
		}
		else
		{
				ft_lstadd_back_token (&head,ft_lstnew_token(ft_getword(str+i),state,WORD));
				i+=count_word(str+i)-1;
		}
		i++;
	}
	
	return head;
}

t_cmd	*parsing(t_token *head, char **env)
{
	t_cmd *cmd;
	if(!check_errors(head))
		return NULL;
	expander(&head,env);
	// aff_lexer(head);
	cmd = parse_tokens(head);
	return (cmd);
}