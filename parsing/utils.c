#include "../minishell.h"
int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}
int is_special(char c)
{
	if (c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '\"' || c == '$' || is_space(c))
		return (1);
	return (0);
}

t_all *static_var(){
	static t_all global;
	return(&global);
}

t_token *lst_skip_spaces(t_token *token)
{
	while(token && token->type == WHITESPACE)
	{
		token = token->next;
	}
	return token;
}
