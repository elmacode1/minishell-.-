#include "minishell.h"

t_token *lst_skip_spaces(t_token *token)
{
	while(token)
	{
			if(token->next->type == WHITESPACE)
				token = token->next;
			else
				return token;
	}
	return NULL;
}
int check_pipes(t_token *token)
{
	if(token->type == PIPE)
		return 0;
	while(token)
	{
		if(token->type == PIPE)
		{
			if(lst_skip_spaces(token->next)->type != WORD)
				return 0;
		}
		token = token->next;
	}
	return 1;

}
int check_squotes(t_token *token)
{
	int flag;

	flag = 1;	
	while(token)
	{
		if(token->type == SQUOTE && flag==1){
			flag = 1;
			token = token->next;
		}
		while(token && token->type != SQUOTE)
			token = token->next;
		if( token && token->type == SQUOTE){
			flag++;
			token = token->next;}
	}
	return flag;
}
int check_dquotes(t_token *token)
{
	int flag;

	flag = 1;	
	while(token)
	{
		if(token->type == DQUOTE && flag==1){
			flag = 1;
			token = token->next;
		}
		while(token && token->type != DQUOTE)
			token = token->next;
		if( token && token->type == DQUOTE){
			flag++;
			token = token->next;}
	}
	return flag;
}
int check_red(t_token *token)
{
	while(token)
	{
		if(token->type == RED_IN || token->type == RED_OUT || token->type == APPEND)
		{
			if(lst_skip_spaces(token->next)->type != WORD)
				return 0;
		}
		token = token->next;
	}
	return 1;
}

int check_errors(t_token *tokens)
{
	//while(tokens)
	//{
		// if ()
		// fd = open("", O_RDONLY);
		// if (fd < 0)
		// 	perror("");
	//}
}
