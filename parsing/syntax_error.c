#include "../minishell.h"

t_token *lst_skip_spaces(t_token *token)
{
	while(token && token->type == WHITESPACE)
	{
		token = token->next;
	}
	return token;
}
int check_pipes(t_token *token)
{
	t_token *next_token;
	if(token->type == PIPE)
		return 0;
	while(token)
	{
		if(token->type == PIPE && token->state== GENERAL)
		{
			next_token = lst_skip_spaces(token->next); //edited here
			if(!next_token)
				return 0;
		}
		token = token->next;
	}
	return 1;

}
int check_squotes(t_token *token)
{
	int count;
	
	count = 0;
	while(token)
	{
		if(token->type == SQUOTE && token->state== GENERAL)
			count ++;
		token = token->next;
	}
	if(count % 2 == 0)
		return (1); //pair num : closed
	return 0;
}
int check_dquotes(t_token *token)
{
	int count;
	
	count = 0;
	while(token)
	{
		if(token->type == DQUOTE && token->state== GENERAL)
			count ++;
		token = token->next;
	}
	if(count % 2 == 0)
		return (1); //pair num : closed
	return 0;
}
int check_red(t_token *token)
{
	t_token *next_token;
	
	while(token)
	{
		if((token->type == RED_IN || token->type == RED_OUT || token->type == HEREDOC || token->type == APPEND )&& token->state== GENERAL)
		{
			next_token = lst_skip_spaces(token->next);
			if(!next_token || next_token->type != WORD)
				return 0;
		}
		token = token->next;
	}
	return 1;
}

int check_errors(t_token *tokens)
{
	if (!check_pipes(tokens))
	{
        printf("minishell: syntax error: invalid pipe usage\n");
        return 0;
    }
    if (!check_red(tokens))
	{
        printf("minishell: syntax error: invalid redirection\n");
        return 0;
    }
    if (check_squotes(tokens) == 0)
	{
        printf("minishell: syntax error: unclosed single quote\n");
        return 0;
    }
    if (check_dquotes(tokens) == 0)
	{
        printf("minishell: syntax error: unclosed double quote\n");
        return 0;
    }
    return 1;
}
