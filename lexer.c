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
t_token *lexer(char *str)
{
	t_token *head;
	t_all *global;

	int i;

	head = NULL;
	i = 0;
	while(str[i])
	{
		if(is_special(str[i]))
		{
			if(str[i]=='|')
				ft_lstadd_back(&head,ft_lstnew("|", PIPE));
			else if(str[i] == ' ')
				ft_lstadd_back(&head,ft_lstnew(" ", WHITESPACE));
			else if(str[i] == '\'')
				ft_lstadd_back(&head,ft_lstnew("\'", SQUOTE));
			else if(str[i] == '\"')
				ft_lstadd_back(&head,ft_lstnew("\"", DQUOTE));
			else if(str[i] == '>' && str[i + 1] && str[i+1] == '>')
			{
				ft_lstadd_back(&head,ft_lstnew(">>", APPEND));
				i++;
			}
			else if(str[i] == '>')
				ft_lstadd_back(&head,ft_lstnew(">", RED_OUT));
			else if(str[i] == '<')
				ft_lstadd_back(&head,ft_lstnew("<", RED_IN));
			else if(str[i] == '\n')
				ft_lstadd_back(&head,ft_lstnew("\n", NEW_LINE));
			else if(str[i] == '$'){
				ft_lstadd_back(&head,ft_lstnew(get_env(str+i), ENV));
				i++;
				i+=count_word(str+i)-1;
			}
		}
		else
		{
			ft_lstadd_back (&head,ft_lstnew(ft_getword(str+i),WORD));
			i+=count_word(str+i)-1;
		}
		i++;
	}

	return head;
}

t_all *static_var(){
	static t_all global;

	return(&global);
}

int main(int ac, char **av, char **env)
{
	char *str;
	t_token *head;
	t_all *global;
	int n;
	int x;

	global=static_var();
	while (1)
	{
		str = readline("minishell~> ");
		if (!str)
			return (0);

		head = lexer(str); // generate tokens
		n = check_squotes(head); // check quotes
		x = check_dquotes(head);

		if (n == 1)
			printf("Syntax error: unclosed single quote\n");
		else if(n >1)
			printf("Quotes are OK \n");
		if (x == 1)
			printf("Syntax error: unclosed double quote\n");
		else if(x > 1)
			printf("Quotes are OK \n");
	}
	global->tokens=head;
	

}
