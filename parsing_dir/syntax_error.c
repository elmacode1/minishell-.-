#include "minishell.h"

t_token *lst_skip_spaces(t_token *token)
{
	while(token)
	{
			if(token->type == WHITESPACE)
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
	int c;

	c = 0;
	flag = 1;	
	while(token)
	{
		if(token->type == SQUOTE && flag==1){
			flag = 1;
			c++;
			token = token->next;
		}
		while(token && token->type != SQUOTE)
			token = token->next;
		if( token && token->type == SQUOTE){
			flag++;
			token = token->next;}
	}
	if(c == 0)
		return -1;
	return flag;
}
int check_dquotes(t_token *token)
{
	int flag;
	int c;

	c = 0;
	flag = 1;	
	while(token)
	{
		if(token->type == DQUOTE && flag==1){
			flag = 1;
			c++;
			token = token->next;
		}
		while(token && token->type != DQUOTE)
			token = token->next;
		if( token && token->type == DQUOTE){
			flag++;
			token = token->next;}
	}
	if(c == 0)
		return -1;
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
	if (!check_pipes(tokens)) {
        printf("Syntax error: invalid pipe usage\n");
        return 0;
    }
    if (!check_red(tokens)) {
        printf("Syntax error: invalid redirection\n");
        return 0;
    }
    if (check_squotes(tokens) == 1) {
        printf("Syntax error: unclosed single quote\n");
        return 0;
    }
    if (check_dquotes(tokens) == 1) {
        printf("Syntax error: unclosed double quote\n");
        return 0;
    }
    return 1;
}
