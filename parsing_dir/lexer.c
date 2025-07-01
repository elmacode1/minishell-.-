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
}																					//echo "malak"'malak'

void *quotes_hander(char c, t_state *state, t_token **head)
{
	static int flag;

	flag = 0;
	if(c == '\"'){
		if(flag == 1 && state ==IN_DQUOTE)
		{
			state = GENERAL;
			flag=0;
		}
		ft_lstadd_back(&head,ft_lstnew("\"", *state, DQUOTE));
		if(state == GENERAL)
		{
		state = IN_DQUOTE;
		flag = 1;
		}
	}
	else if(c == '\''){
		if(flag == 1 && state==IN_SQUOTE){
			state = GENERAL;
			flag=0;
		}
		ft_lstadd_back(&head, ft_lstnew("\'", *state, SQUOTE));
		if(state == GENERAL && flag ==0)
		state = IN_SQUOTE;
		flag = 1;
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
			else if(is_space(str[i]))
				ft_lstadd_back(&head,ft_lstnew(" ",state ,WHITESPACE));
			else if(str[i] == '\'' || str[i] == '\"')
				quotes_hander(str[i], &state, &head);
			else if(str[i] == '>' && str[i + 1] && str[i+1] == '>')
			{
				ft_lstadd_back(&head,ft_lstnew(">>",state, APPEND));
				i++;
			}
			else if(str[i] == '>')
				ft_lstadd_back(&head,ft_lstnew(">",state ,RED_OUT));
			else if(str[i] == '<')
				ft_lstadd_back(&head,ft_lstnew("<",state ,RED_IN));
			else if(str[i] == '\n')
				ft_lstadd_back(&head,ft_lstnew("\n",state, NEW_LINE));
			else if(str[i] == '$'){
				ft_lstadd_back(&head,ft_lstnew(get_env(str+i),state, ENV));
				i++;
				i+=count_word(str+i)-1;
			}
			else
			{
				ft_lstadd_back (&head,ft_lstnew(ft_getword(str+i),state,WORD));
				i+=count_word(str+i)-1;
			}
			i++;
		}
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
		// head = lst_skip_spaces(head);
		check_errors(head);
		command = parse_tokens(head);
		args = command->argv;
		int i = 0;
		while (command)
		{
			while (args[i])
			{
				printf("arg[%d] == %s\n", i, args[i]);
				i++;
			}
			printf("command->append == %d\n", command->append);
			printf("command->infile == %s\n", command->infile);
			printf("command->outfile == %s\n", command->outfile);
			command = command->next;
		}
	}
}
