#include "minishell.h"

char *ft_getword(char *s)
{
	int c;
	char *str;
	
	c = count_word(s);
	str = malloc(sizeof(char)*(c+1));
	ft_strlcpy(str,s,c+1);
	return str;
}
char *get_env(char *s)
{
	int c;
	char *str;

	c = count_word(s+1);
	str = malloc(sizeof(char)*(c+2));  
	ft_strlcpy(str,s,c+2);
	return str;
}

void *quotes_hander(char c, t_state *state, t_token **head)
{
	if(c == '\"'){

		
		if(*state ==IN_DQUOTE)
		{
			*state = GENERAL;
			ft_lstadd_back(head,ft_lstnew("\"", *state, DQUOTE));
		}
		else if (*state == GENERAL)
		{
			ft_lstadd_back(head,ft_lstnew("\"", *state, DQUOTE));
			*state = IN_DQUOTE;
		}
		else
		{
			ft_lstadd_back(head,ft_lstnew("\"", *state, DQUOTE));
		}
	}
	else if(c == '\''){
		if(*state ==IN_SQUOTE)
		{
			*state = GENERAL;
			ft_lstadd_back(head,ft_lstnew("\'", *state, SQUOTE));
		}
		else if (*state == GENERAL)
		{
			ft_lstadd_back(head,ft_lstnew("\'", *state, SQUOTE));
			*state = IN_SQUOTE;
		}
		else
		{
			ft_lstadd_back(head,ft_lstnew("\'", *state, SQUOTE));
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
				ft_lstadd_back(&head,ft_lstnew("|",state ,PIPE));
			else if(is_space(str[i])){
				ft_lstadd_back(&head,ft_lstnew(" ",state ,WHITESPACE));
			}
			else if(str[i] == '\'' || str[i] == '\"')
				quotes_hander(str[i], &state, &head);

			else if(str[i] == '>' && str[i + 1] && str[i+1] == '>')
			{
				ft_lstadd_back(&head,ft_lstnew(">>",state, APPEND));
				i++;
			}
			else if(str[i] == '<' && str[i + 1] && str[i+1] == '<')
			{
				ft_lstadd_back(&head,ft_lstnew("<<",state, HEREDOC));
				i++;
			}
			else if(str[i] == '>')
				ft_lstadd_back(&head,ft_lstnew(">",state ,RED_OUT));
			else if(str[i] == '<')
				ft_lstadd_back(&head,ft_lstnew("<",state ,RED_IN));
			else if(str[i] == '\n')
				ft_lstadd_back(&head,ft_lstnew("\n",state, NEW_LINE));
			else if(str[i] == '$'){
				if(str[i+1] == '?')
					ft_lstadd_back(&head,ft_lstnew("$?",state, ENV));
				else 
				{
					ft_lstadd_back(&head,ft_lstnew(get_env(str+i),state, ENV));
					i++;
					i+=count_word(str+i)-1;
				}
			}
		}
		else
		{
				ft_lstadd_back (&head,ft_lstnew(ft_getword(str+i),state,WORD));
				i+=count_word(str+i)-1;
		}
		i++;
	}
	
	return head;
}

int main(int ac, char **av, char **env)
{
	char *str;
	t_token *head;
	// t_all *global;
	t_cmd *command;
	char	**args;

	// global=static_var();
	while (1)
	{
		str = readline("minishell~> ");
		if (!str)
			return (0);

		head = lexer(str);
		check_errors(head);
		head = lst_skip_spaces(head);
		command = parse_tokens(head);
		while (command)
        {
            // Print command arguments
            if (command->argv)
            {
                int i = 0;
                while (command->argv[i])
                {
                    printf("arg[%d] == %s\n", i, command->argv[i]);
                    i++;
                }
            }
            
            // Print redirections
            t_redirect *redirect = command->redirections;
            while (redirect)
            {
                printf("redirection: %s (type: %d)\n", redirect->filename, redirect->type);
                redirect = redirect->next;
            }
            
            command = command->next;
        }
	}
}
