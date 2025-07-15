#include "minishell.h"
void	add_arg(char ***argv, int *argc, char *arg)
{
    *argv = realloc(*argv, sizeof(char*) * (*argc + 2)); // Reallocate argv to hold one more string (+1 for new, +1 for NULL)
    (*argv)[*argc] = strdup(arg);
    (*argc)++;
    (*argv)[*argc] = NULL;
}
t_cmd	*new_cmd() 
{
    t_cmd *new;
	new = malloc(sizeof(t_cmd));
    if (!new)
		return NULL;
    new->argv = NULL;
	new->redirections = NULL;
    new->next = NULL;
    return new;
}

void	add_redirection(t_cmd *cmd, char *filename, int type)
{
	// Create new redirection node
	t_redirect *new_redirect;
	new_redirect = malloc(sizeof(t_redirect));
	new_redirect->filename = strdup(filename);
	new_redirect->type = type;
	new_redirect->next = NULL;

// Add to the end of the list
	if (!cmd->redirections)
	{
		cmd->redirections = new_redirect;
	}
	else
	{
		t_redirect *last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redirect;
	}
}

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *cmd_head;
	t_cmd *cmd_last;
	t_cmd *curent_cmd;

	cmd_head = NULL;
	cmd_last = NULL;
	curent_cmd = NULL;

    t_token *tok = tokens;
    char **argv = NULL;
    int argc = 0;

    while (tok)
	{
        if (!curent_cmd)
		{
            curent_cmd = new_cmd();
            argv = NULL;
            argc = 0;
        }
        if (tok->type == WORD)
			add_arg(&argv, &argc, tok->text);//adding the arg to the list;
		else if (tok->type == RED_IN)
		{
			tok = lst_skip_spaces(tok->next);
            if (tok && tok->type == WORD)
			{
               add_redirection(curent_cmd, tok->text, RED_IN);
			   tok = tok->next;
			   continue;
			}
        } 
		else if (tok->type == RED_OUT)
		{
			tok = lst_skip_spaces(tok->next);
            if (tok && tok->type == WORD)
			{
                add_redirection(curent_cmd, tok->text, RED_OUT);
				tok = tok->next;
				continue;
            }
        }
		else if (tok->type == APPEND)
		{
			tok = lst_skip_spaces(tok->next);
            if (tok && tok->type == WORD)
			{
                add_redirection(curent_cmd, tok->text, APPEND);
				tok = tok->next;
				continue;
            }
        }
		else if (tok->type == PIPE)
		{
            curent_cmd->argv = argv;
            if (!cmd_head)
                cmd_head = curent_cmd;
            else
                cmd_last->next = curent_cmd;
            cmd_last = curent_cmd;
            curent_cmd = NULL;
			argv = NULL;
			argc = 0;
        }
        if(tok)
			tok = tok->next;
    }
    //handling last cmd
    if (curent_cmd)
	{
        curent_cmd->argv = argv;
        if (!cmd_head)
            cmd_head = curent_cmd;
        else
            cmd_last->next = curent_cmd;
    }
    return cmd_head;
}