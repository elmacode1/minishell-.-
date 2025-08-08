#include "../minishell.h"

int	is_redirect_token(t_token *t)
{
	return (t->type == RED_IN || t->type == RED_OUT
		|| t->type == APPEND || t->type == HEREDOC);
}

char	*parse_quoted_redirect(t_token **tokens)
{
	char		*value = NULL;
	t_tokentype	quote;

	quote = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	while (*tokens && !((*tokens)->type == quote && (*tokens)->state == GENERAL))
	{
		char *old = value;
		value = ft_strjoin(value, (*tokens)->text);
		if (old)
			free(old);
		(*tokens) = (*tokens)->next;
	}
	if (*tokens && (*tokens)->type == quote && (*tokens)->state == GENERAL)
		(*tokens) = (*tokens)->next;
	return value;
}
char	*redirect_target(t_token **tokens)
{
	char	*res = NULL;

	*tokens = lst_skip_spaces(*tokens);
	if (*tokens && ((*tokens)->type == DQUOTE || (*tokens)->type == SQUOTE) && (*tokens)->state == GENERAL)
		res = parse_quoted_redirect(tokens);
	else if (*tokens)
	{
		res = ft_strdup2((*tokens)->text);
		(*tokens) = (*tokens)->next;
	}
	return res;
}
void	parse_redirect(t_token **tokens, t_cmd *cmd)
{
	t_tokentype	t;
	char		*target;

	t = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	target = redirect_target(tokens);
	add_redirection(cmd, target, t);
	if (target)
		free(target);
}