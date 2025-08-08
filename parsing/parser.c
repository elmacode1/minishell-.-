#include "../minishell.h"

void append_token_text(char **tmp, t_token **tokens)
{
	char *old = *tmp;
	*tmp = ft_strjoin(*tmp, (*tokens)->text);
	if (old)
		free(old);
	(*tokens) = (*tokens)->next;
}
void parse_inside_quotes(char **tmp, t_token **tokens, t_tokentype quote)
{
	while (*tokens && !((*tokens)->type == quote && (*tokens)->state == GENERAL))
		append_token_text(tmp, tokens);
	if (*tokens && (*tokens)->type == quote && (*tokens)->state == GENERAL)
		(*tokens) = (*tokens)->next;
}
void parse_next_word(char **tmp, t_token **tokens)
{
	if (((*tokens)->type == DQUOTE || (*tokens)->type == SQUOTE) && (*tokens)->state == GENERAL)
	{
		t_tokentype quote = (*tokens)->type;
		(*tokens) = (*tokens)->next;
		parse_inside_quotes(tmp, tokens, quote);
	}
	else
		append_token_text(tmp, tokens);
}

int	parse_word_group(t_token **tokens, char **argv)
{
	char	*tmp = NULL;
	int		count = 0;
	while (*tokens && !(((*tokens)->type == WHITESPACE || (*tokens)->type == RED_IN
		|| (*tokens)->type == RED_OUT || (*tokens)->type == APPEND
		|| (*tokens)->type == HEREDOC) && (*tokens)->state == GENERAL))
		parse_next_word(&tmp, tokens);
	if (tmp)
	{
		*argv = ft_strdup2(tmp);
		free(tmp);
		count++;
	}
	return count;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd = NULL;
	while (tokens)
	{
		t_cmd	*new = new_cmd();
		int		max_args = count_tokens(tokens);
		char	**argv = malloc(sizeof(char *) * (max_args + 1));
		free_helper(argv);
		int		i = 0;
		while (tokens && !(tokens->type == PIPE && tokens->state == GENERAL))
		{
			if (tokens->type == WORD && !ft_strcmp(tokens->text, ""))
				tokens = tokens->next;
			else if (tokens->type == WORD || tokens->type == DQUOTE || tokens->type == SQUOTE)
				i += parse_word_group(&tokens, argv + i);
			else if (tokens->type == EMPTY_STR)
				argv[i++] = ft_strdup2("");
			else if (is_redirect_token(tokens))
				parse_redirect(&tokens, new);
			else
				tokens = tokens->next;
		}
		argv[i] = NULL;
		new->argv = argv;
		ft_lstadd_back_cmd(&cmd, new);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return cmd;
}