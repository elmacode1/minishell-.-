#include "../minishell.h"

void	process_double_quotes(char *c, t_state *state, t_token **head)
{
    if (c[1] == '\"' && *state == GENERAL)
        ft_lstadd_back_token(head, ft_lstnew_token("", *state, EMPTY_STR));
    else if (*state == IN_DQUOTE)
    {
        *state = GENERAL;
        ft_lstadd_back_token(head, ft_lstnew_token("\"", *state, DQUOTE));
    }
    else if (*state == GENERAL)
    {
        ft_lstadd_back_token(head, ft_lstnew_token("\"", *state, DQUOTE));
        *state = IN_DQUOTE;
    }
    else
        ft_lstadd_back_token(head, ft_lstnew_token("\"", *state, DQUOTE));
}

void	process_single_quotes(char *c, t_state *state, t_token **head)
{
    if (c[1] == '\'' && *state == GENERAL)
        ft_lstadd_back_token(head, ft_lstnew_token("", *state, EMPTY_STR));
    else if (*state == IN_SQUOTE)
    {
        *state = GENERAL;
        ft_lstadd_back_token(head, ft_lstnew_token("\'", *state, SQUOTE));
    }
    else if (*state == GENERAL)
    {
        ft_lstadd_back_token(head, ft_lstnew_token("\'", *state, SQUOTE));
        *state = IN_SQUOTE;
    }
    else
        ft_lstadd_back_token(head, ft_lstnew_token("\'", *state, SQUOTE));
}

void	quotes_handler(char *c, t_state *state, t_token **head)
{
    if (c[0] == '\"')
        process_double_quotes(c, state, head);
    else if (c[0] == '\'')
        process_single_quotes(c, state, head);
}